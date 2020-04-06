%{
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "defs.h"
#include "common.h"

#include "y.tab.h"

void yyerror(char *);
int yyparse(node_t * program_root);
int fileno(FILE * stream);
void analyse_tree(node_t root);


char * infile = NULL;
char * outfile = NULL;
bool stop_after_syntax = false;
bool stop_after_verif = false;
/* A completer */

#if YYDEBUG
extern int yydebug;
#endif


%}

%option yylineno


LETTRE          [a-zA-Z]
/* A completer ; fausses definitions pour que lex ne fasse pas d'erreur */
CHIFFRE 	[0-9]
IDF             {LETTRE}({LETTRE}|{CHIFFRE}|_)*
CHIFFRE_NON_NUL	[1-9]
ENTIER_DEC	0|{CHIFFRE_NON_NUL}({CHIFFRE})*
LETTRE_HEXA     [a-fA-F]
ENTIER_HEXA	0x({CHIFFRE}|{LETTRE_HEXA})+
SIGNE		-| 
/*ENTIER          {SIGNE}({ENTIER_DEC}|{ENTIER_HEXA})*/
ENTIER 		0
CHAINE_CAR      [ -!#-[]-~]*
CHAINE          "({CHAINE_CAR}|\"|\n)"
COMMENTAIRE     "(/*{CHAINE}*/)"

%%

"void"          return TOK_VOID;






{IDF} {
                yylval.strval = strdup(yytext);
                return TOK_IDENT;
}

{ENTIER} {
                /* A completer : affecter yylval.intval et faire des verifications */
                return TOK_INTVAL;
}

{CHAINE} {
                /* A completer : affecter yylval.strval */
                return TOK_STRING;
}

{COMMENTAIRE} {
}


[ \t\n]+

. {
                fprintf(stderr, "Error line %d: Lexical error\n", yylineno);
                exit(1);
}


%%

int yywrap(void) {
    return 1;
}


int main(int argc, char ** argv) {
    /* A completer */
    node_t program_root;
    parse_args(argc, argv);
    #if YYDEBUG
    yydebug = 1;
    #endif

    yyin = fopen(infile, "r");
    yyparse(&program_root);
    fclose(yyin);
    analyse_tree(program_root);
    yylex_destroy();
    return 0;
}
