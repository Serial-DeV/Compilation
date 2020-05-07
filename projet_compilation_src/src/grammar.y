%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "defs.h"
#include "common.h"
#include "mips_inst.h"



/* Global variables */
/* A completer */
extern bool stop_after_syntax;
extern bool stop_after_verif;
extern char * infile;
extern char * outfile;

/* prototypes */
int yylex(void);
extern int yylineno;

void yyerror(node_t * program_root, char * s);
void analyse_tree(node_t root);
node_t make_node(node_nature nature, int nops, ...);
/* A completer */

%}

%parse-param { node_t * program_root }

%union {
    int32_t intval;
    char * strval;
    node_t ptr;
};


/* Definir les token ici avec leur associativite, dans le bon ordre */
%token TOK_VOID TOK_INT TOK_INTVAL TOK_BOOL TOK_TRUE TOK_FALSE
%token TOK_IDENT TOK_IF TOK_ELSE TOK_WHILE TOK_FOR TOK_PRINT
%token TOK_AFFECT TOK_GE TOK_LE TOK_GT TOK_LT TOK_EQ
%token TOK_NE TOK_PLUS TOK_MINUS TOK_MUL TOK_DIV TOK_MOD
%token TOK_UMINUS TOK_SEMICOL TOK_COMMA TOK_LPAR TOK_RPAR TOK_LACC
%token TOK_RACC TOK_STRING TOK_DO


%nonassoc TOK_THEN
%nonassoc TOK_ELSE

%right TOK_AFFECT

%left TOK_OR
%left TOK_AND
%left TOK_BOR
%left TOK_BXOR
%left TOK_BAND
%left TOK_EQ TOK_NE
%left TOK_GT TOK_LT TOK_GE TOK_LE
%left TOK_SRL TOK_SRA TOK_SLL

%left TOK_PLUS TOK_MINUS
%left TOK_MUL TOK_DIV TOK_MOD

%left TOK_UMINUS TOK_NOT TOK_BNOT

%type <intval> TOK_INTVAL
%type <strval> TOK_IDENT TOK_STRING
%type <ptr> program listdecl listdeclnonnull vardecl ident type listtypedecl decl maindecl
%type <ptr> listinst listinstnonnull inst block expr listparamprint paramprint



%%

/* Regles ici */
program:
        listdeclnonnull maindecl
        {
            $$ = make_node(NODE_PROGRAM, 2, $1, $2);
            *program_root = $$;
        }
        | maindecl
        {
            $$ = make_node(NODE_PROGRAM, 2, NULL, $1);
            *program_root = $$;
        }
        ;

listdeclnonnull:
            { $$ = NULL; }
        ;

maindecl:
            { $$ = NULL; }
        ;


listdecl: 
	listdeclnonnull
	|
	;

listdeclnonnull:
	vardecl
	| listdeclnonnull vardecl
	;

vardecl: 
	type listtypedecl TOK_SEMICOL
	;

type:
	TOK_INT
	| TOK_BOOL
	| TOK_VOID
	;

listtypedecl:
	decl
	| listtypedecl TOK_COMMA decl
	;

decl:
	ident
	| ident TOK_AFFECT expr
	;

maindecl:
	type ident TOK_LPAR TOK_RPAR block
	;

listinst:
	listinstnonnull
	|
	;

listinstnonnull:
	inst
	| listinstnonnull inst
	;



inst:
	expr TOK_SEMICOL
	|TOK_IF TOK_LPAR expr TOK_RPAR inst TOK_ELSE inst
	|TOK_IF TOK_LPAR expr TOK_RPAR inst %prec TOK_THEN
	|TOK_WHILE TOK_LPAR expr TOK_RPAR inst
	|TOK_FOR TOK_LPAR expr TOK_SEMICOL expr TOK_SEMICOL expr TOK_RPAR inst
	|TOK_DO inst TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SEMICOL
	|block
	|TOK_SEMICOL
	|TOK_PRINT TOK_LPAR listparamprint TOK_RPAR TOK_SEMICOL
	;

block:
	TOK_LACC listdecl listinst TOK_RACC
	;

expr:
	expr TOK_MUL expr
	|expr TOK_DIV expr
	|expr TOK_PLUS expr
	|expr TOK_MINUS expr
	|expr TOK_MOD expr
	|expr TOK_LT expr
	|expr TOK_GT expr
	|TOK_MINUS expr %prec TOK_UMINUS
	|expr TOK_GE expr
	|expr TOK_LE expr
	|expr TOK_EQ expr
	|expr TOK_NE expr
	|expr TOK_AND expr
	|expr TOK_OR expr
	|expr TOK_BAND expr
	|expr TOK_BOR expr
	|expr TOK_BXOR expr
	|expr TOK_SRL expr
	|expr TOK_SRA expr
	|expr TOK_SLL expr
	|TOK_NOT expr
	|TOK_BNOT expr
	|TOK_LPAR expr TOK_RPAR
	|ident TOK_AFFECT expr
	|TOK_INTVAL
	|TOK_TRUE
	|TOK_FALSE
	|ident
	;

listparamprint:
	listparamprint TOK_COMMA paramprint
	| paramprint
	;

paramprint:
	ident
	| TOK_STRING
	;

ident:
	TOK_IDENT
	;


%%

/* A completer et/ou remplacer avec d'autres fonctions */
node_t make_node(node_nature nature, int nops, ...) {
    va_list ap;

    return NULL;
}



/* A completer */
void analyse_tree(node_t root) {
    if (!stop_after_syntax) {
        // Appeler la passe 1

        if (!stop_after_verif) {
            create_program(); 
            // Appeler la passe 2

            dump_mips_program(outfile);
            free_program();
        }
        free_global_strings();
    }
}



void yyerror(node_t * program_root, char * s) {
    fprintf(stderr, "Error line %d: %s\n", yylineno, s);
    exit(1);
}

