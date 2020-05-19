#include "passe1.h"

extern char* message;


void passe1(node_t node)
{
  node_nature nature = node->nature;
  yylineno = node->lineno;

  switch (nature)
  {
    case NODE_PROGRAM :
      push_global_context();
      break;
    case NODE_BLOCK :
      push_context();
      break;
    case NODE_LIST :

      break;
    case NODE_DECLS :
      break;
    case NODE_DECL :
      break;
    case NODE_IDENT :
      break;
    case NODE_TYPE :
      break;
    case NODE_INTVAL :
      break;
    case NODE_BOOLVAL :
      break;
    case NODE_STRINGVAL :
      break;
    case NODE_FUNC :
      break;
    case NODE_IF :
      break;
    case NODE_WHILE :
      break;
    case NODE_FOR :
      break;
    case NODE_DOWHILE :
      break;

    // Opérations entre 1 ou 2 nombres, vérification du type des arguments
    case NODE_PLUS :
    case NODE_MINUS :
    case NODE_MUL :
    case NODE_DIV :
    case NODE_MOD :
    case NODE_BAND :
    case NODE_BOR :
    case NODE_BXOR :
    case NODE_SLL :
    case NODE_SRA :
    case NODE_SRL :
    case NODE_LT :
    case NODE_GT :
    case NODE_LE :
    case NODE_GE :
      if(node->opr[0]->type != TYPE_INT || node->opr[1]->type != TYPE_INT)
      {
        sprintf(message, "Un des arguments n'est pas de type TYPE_INT");
        yyerror(&node, message);
      }
      break;

      // Opérations entre 1 ou 2 nombres qui retournent un entier, vérification du type des arguments
    case NODE_AND :
    case NODE_OR :
      if(node->opr[0]->type != TYPE_BOOL || node->opr[1]->type != TYPE_BOOL)
      {
        sprintf(message, "Un des arguments n'est pas de type TYPE_BOOL");
      }
      break;

    //Cas spéciaux
    case NODE_EQ :
    case NODE_NE :
    case NODE_NOT :
      break;
    case NODE_BNOT :
      break;

    case NODE_UMINUS :
      break;
    case NODE_AFFECT :
      break;
    case NODE_PRINT :
      break;
    default :
      printf("\nNature du node non reconnue.\n\n");
      break;
  }
}
