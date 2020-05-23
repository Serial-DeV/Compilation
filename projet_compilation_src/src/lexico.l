%{
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "defs.h"
#include "common.h"
#include "y.tab.h"
#include "passe1.h"

void yyerror(node_t * program_root, char * s);
int yyparse(node_t * program_root);
int fileno(FILE * stream);
void analyse_tree(node_t root);


char * infile = NULL;
char * outfile = NULL;
bool stop_after_syntax = false;
bool stop_after_verif = false;
char* message;
int niveau_trace = 0;
int32_t nb_registres = 8;

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
COMMENTAIRE     "//".*$

%%

"void"   {
					if(niveau_trace >= 1)
					{
								printf("void détecté\n");
					}

					return TOK_VOID;
				 }
"int"		  {
					if(niveau_trace >= 1)
					{
								printf("int détecté\n");
					}
				return TOK_INT;
				  }
"bool"		{
					if(niveau_trace >= 1)
					{
								printf("bool détecté\n");
					}
					return TOK_BOOL;
					}
"true"    {
					printf("true détecté\n");
					return TOK_TRUE;
					}
"false"   {
						if(niveau_trace >= 1)
						{
									printf("false détecté\n");
						}
						return TOK_FALSE;
					}
"if"  		{
						if(niveau_trace >= 1)
						{
									printf("if détecté\n");
						}
					return TOK_IF;
					}
"else"    {
						if(niveau_trace >= 1)
						{
									printf("else détecté\n");
						}
					return TOK_ELSE;
					}
"while"   {
						if(niveau_trace >= 1)
						{
									printf("while détecté\n");
						}
					return TOK_WHILE;
					}
"for"  		{
						if(niveau_trace >= 1)
						{
									printf("for détecté\n");
						}
					return TOK_FOR;
					}
"print"   {
						if(niveau_trace >= 1)
						{
									printf("print détecté\n");
						}
					return TOK_PRINT;
					}
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
";"    		return TOK_SEMICOL;
","    		return TOK_COMMA;
"("    		return TOK_LPAR;
")"   		return TOK_RPAR;
"{"    		return TOK_LACC;
"}"    		return TOK_RACC;
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
			if(niveau_trace >= 1)
			{
						printf("IDF détecté\n");
			}

		yylval.strval = strdup(yytext);
                return TOK_IDENT;
}

{ENTIER} {
		/* A completer : affecter yylval.intval et faire des verifications */

		if(niveau_trace >= 1)
		{
					printf("Entier détecté\n");
		}

		if((strlen(yytext) >= strlen("2147483647") && strcmp("2147483647", yytext) < 0) || (strlen(yytext) >= strlen("-2147483648") && strcmp("-2147483648", yytext) < 0))
		{
		 fprintf(stderr, "Error line %d: integer out of range\n", yylineno);
		 exit(-1);
		}
		yylval.intval = atoi(yytext); // Vérifier ce qu'il faut vérifier
                return TOK_INTVAL;
}

{CHAINE} {
                /* A completer : affecter yylval.strval */

		if(niveau_trace >= 1)
		{
					printf("Chaîne détecté\n");
		}

		yylval.strval = strdup(yytext);
                return TOK_STRING;
}

{COMMENTAIRE} {
		if(niveau_trace >= 1)
		{
					printf("Commentaire détecté\n");
		}
}


[ \t\n]+

. {
                fprintf(stderr, "Error line %d: Lexical error\n", yylineno);
                exit(-1);
}


%%

int yywrap(void) {
    return 1;
}


int main(int argc, char ** argv)
{
    /* A completer */

    node_t program_root;
    printf("\nAvant le parse args\n\n");

    parse_args(argc, argv);
    printf("\nSortie de parse args\n\n");
    #if YYDEBUG
    yydebug = 1;
    #endif

    printf("\nVerification lexicale\n\n");
    yyin = fopen(infile, "r");
    //while(yylex());

    printf("\nAvant le yyparse\n\n");

    yyparse(&program_root);


    printf("\nAvant le dump 1\n\n");
    dump_tree(program_root, "fichier_dump.dot");

		printf("\nAvant l'analyse tree\n\n");
		analyse_tree(program_root);
		printf("\nAprès l'analyse tree\n\n");

		printf("\nAvant le dump 2\n\n");
    dump_tree(program_root, "fichier_dump_fin.dot");
		
    fclose(yyin);
    yylex_destroy();
    return 0;
}
