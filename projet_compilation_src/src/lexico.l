%{
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "defs.h"
#include "common.h"

// Ajout seulement pour le test
#include "context.h"

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
SIGNE		\-|\+
ENTIER          {SIGNE}?({ENTIER_DEC}|{ENTIER_HEXA})
/*CHAINE_CAR      [ -!#-[]-~]* */		
CHAINE_CAR	([\040-\176])+

CHAINE          ["]({CHAINE_CAR}|[\"]|[\n])*["]
COMMENTAIRE     "//"({CHAINE_CAR})*"\n"

%%

"void"          {printf("void détecté\n");return TOK_VOID;}
"int"		{printf("int détecté\n");return TOK_INT;}
"bool"   	{printf("bool détecté\n");return TOK_BOOL;}
"true"    	{printf("true détecté\n");return TOK_TRUE;}
"false"    	{printf("false détecté\n");return TOK_FALSE;}
"if"  		return TOK_IF;
"else"    	return TOK_ELSE;
"while"   	return TOK_WHILE;
"for"  		return TOK_FOR;
"print"   	{printf("print détecté\n");return TOK_PRINT;}
"="    		return TOK_AFFECT;
"<="    	return TOK_GE;
">="    	return TOK_LE;
">"    		return TOK_GT;
"<"    		return TOK_LT;
"=="    	return TOK_EQ;
"!="    	return TOK_NE;
"+"    		return TOK_PLUS;
"-"    		return TOK_MINUS;
"*"    		return TOK_MUL;
"/"    		return TOK_DIV;
"%"    		return TOK_MOD;/*
"-"    		return TOK_UMINUS;*/
";"    		{printf(" ; détecté\n");return TOK_SEMICOL;}
","    		return TOK_COMMA;
"("    		{printf(" ( détecté\n");return TOK_LPAR;}
")"   		{printf(" ) détecté\n");return TOK_RPAR;}
"{"    		{printf(" { détecté\n");return TOK_LACC;}
"}"    		{printf(" } détecté\n");return TOK_RACC;}
"do"    	return TOK_DO;
"then"   	return TOK_THEN;
"||"		return TOK_OR;
"&&"  		return TOK_AND;
"|"    		return TOK_BOR;
"^"    		return TOK_BXOR;
"&"    		return TOK_BAND;
">>>"    	return TOK_SRL;
">>"    	return TOK_SRA;
"<<"   		return TOK_SLL;
"!"    		return TOK_NOT;
"~"    		return TOK_BNOT;





{IDF} {
		printf("IDF détecté\n");                
		yylval.strval = strdup(yytext);
                return TOK_IDENT;
}

{ENTIER} {
		/* A completer : affecter yylval.intval et faire des verifications */
		printf("Entier détecté\n");                
		yylval.intval = atoi(yytext); // Vérifier ce qu'il faut vérifier
                return TOK_INTVAL;
}

{CHAINE} {
                /* A completer : affecter yylval.strval */
		printf("Chaine détectée\n");
		yylval.strval = strdup(yytext);
                return TOK_STRING;
}

{COMMENTAIRE} {
	printf("Commentaire détecté\n");
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
    printf("\nAvant le parse\n\n");
        
    parse_args(argc, argv);
    printf("\nSortie de parse\n\n");
    #if YYDEBUG
    yydebug = 1;
    #endif
   
    printf("\nVerification lexicale\n\n");
    yyin = fopen(infile, "r");
    //while(yylex());
    
    printf("\nAvant le yyparse\n\n");

    yyparse(&program_root);
    if (stop_after_syntax)
    {
		printf("\nOn s'arrête après l'analyse syntaxique\n\n");
		return 0;
    }
    
    
    printf("\nAvant le dump\n\n");
    dump_tree(program_root, "fichier_dump.dot");
    printf("\nAprès le dump\n\n");
    
    fclose(yyin);
    //analyse_tree(program_root);
    yylex_destroy();
    return 0;
}
