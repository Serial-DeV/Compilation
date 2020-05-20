#include "passe1.h"

bool error_exit = false; //Si il y a une erreur, on continue, mais on ne finit pas la compilation
//Le mettre à true partout où il y a une erreur et implémenter l'exit
node_type dernier_type_rencontre;
const char * dernier_type_string;

bool decl, affect, init = false;

void passe1(node_t node)
{
  node_nature nature = node->nature;
  yylineno = node->lineno;

  const char * nature_string = node_nature2string(node->nature);
  const char * type_string = node_type2string(node->type);


  //Pour le debug




  printf("\nJe suis dans le node : %s\n", nature_string);
  printf("Le type du node est : %s\n", type_string);
  printf("Le dernier node type rencontré est : %s\n", dernier_type_string);

  printf("Avant switch\n");

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

      if (strcmp(node->ident,"main") == 0)
      {

        //C'est le main
        if(dernier_type_rencontre != TYPE_VOID)
        {
          //printf("\nJe suis là ??\n");
          yyerror(&node, "Le main n'est pas de type void.");
        }
      }
      //printf("\nJe suis là..\n");

      break;
    case NODE_TYPE :
      dernier_type_rencontre = node->type;
      dernier_type_string = node_type2string(dernier_type_rencontre);
      break;
    case NODE_INTVAL :
/*
      if(dernier_type_rencontre != node->type)
      {
        yyerror(&node, "Conflit entre un type 'int' et un type 'bool'.");
      }
    */
      break;
    case NODE_BOOLVAL :
/*
      if(dernier_type_rencontre != node->type)
      {
        yyerror(&node, "Conflit entre un type 'int' et un type 'bool'.");
      }
*/
      break;
    case NODE_STRINGVAL :
      node->offset = add_string(node->str); //ajoute la declaration en .data et retourne l'offset
      break;
    case NODE_FUNC :
      //A appeler au début de l'anamyse d'une fonction
      reset_env_current_offset(); //reset l'offset courant à 0
      reset_temporary_max_offset(); //reset l'offset maximum pour les temporaires
      set_max_registers(nb_registres); //définit le nombre maximal de registres à utiliser
      break;
    case NODE_IF :
      if (node->opr[0]->type != TYPE_BOOL)
      {
        yyerror(&node, "La condition n'est pas de type 'bool'.");
      }
      break;
    case NODE_WHILE :
      if (node->opr[0]->type != TYPE_BOOL)
      {
        yyerror(&node, "La condition n'est pas de type 'bool'.");
      }
      break;
    case NODE_FOR :
      if (node->opr[1]->type != TYPE_BOOL)
      {
        yyerror(&node, "La condition n'est pas de type 'bool'.");
      }
      break;
    case NODE_DOWHILE :
      if (node->opr[1]->type != TYPE_BOOL)
      {
        yyerror(&node, "La condition n'est pas de type 'bool'.");
      }
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
        yyerror(&node, "Un des arguments n'est pas de type 'int'");
      }
      break;

      // Opérations entre 1 ou 2 nombres qui retournent un entier, vérification du type des arguments
    case NODE_AND :
    case NODE_OR :
      if(node->opr[0]->type != TYPE_BOOL || node->opr[1]->type != TYPE_BOOL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'bool'");
      }
      break;

    //On vérifie que la comparaison se fait entre deux noeuds de même type
    case NODE_EQ :
    case NODE_NE :
      if(node->opr[0]->type != node->opr[1]->type)
      {
        yyerror(&node, "Les arguments ne sont pas du même type.");
      }
      break;
    case NODE_NOT :
      if(node->opr[0]->type != TYPE_BOOL)
      {
        yyerror(&node, "L'argument n'est pas de type 'bool'");
      }
      break;
    case NODE_BNOT :
    case NODE_UMINUS :
      if(node->opr[0]->type != TYPE_INT)
      {
        yyerror(&node, "L'argument n'est pas de type 'int'.");
      }
      break;
    case NODE_AFFECT :
      break;
    case NODE_PRINT :
      break;
    default :
      printf("\nNature du node non reconnue.\n\n");
      break;
  }
  printf("Après switch\n");

  if (nature == NODE_DECLS)
  {
    printf("Dans le if du DECLS\n");

    node_type type1 = node->opr[0]->type; //Le type déclaré
    node_type type3 = node->opr[1]->opr[1]->type; //Le type réellement affecté
    /*
    const char * type_string1 = node_type2string(type1);
    const char * type_string3 = node_type2string(type3);

    printf("\nType déclaré 1 : %s\n", type_string1);
    printf("\nType déclaré 3 : %s\n", type_string3);
    */
    if(type1 != type3)
    {
      yyerror(&node, "Le type déclaré est différent du type affecté.");

    }

  }

  printf("Passe 1 sur les arguments\n");

  int i;
  if (node->nops > 0)
  {
    for (i = 0; i < node->nops; i++)
    {
      if(node->opr[i] != NULL)
      {
        passe1(node->opr[i]);
      }
      else
      {
        printf("Noeud NULL\n");
      }
    }
  }
  else
  {
    printf("Pas d'arguments\n");
  }
  //On arrive ici à la fin de la passe, lorsque l'on veut dépiler des contextes par exemple
  switch (nature)
  {
    case NODE_FUNC :
      node->offset = get_env_current_offset();
      node->stack_size = get_temporary_max_offset();
      break;
    case NODE_BLOCK :
      pop_context();
      break;
    case NODE_LIST :

      break;
    case NODE_DECLS :
      break;
    case NODE_DECL :
      break;
    default:
      break;
  }

}
