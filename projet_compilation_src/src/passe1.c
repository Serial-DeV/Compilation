#include "passe1.h"

bool error_exit = false; //Si il y a une erreur, on continue, mais on ne finit pas la compilation
//Le mettre à true partout où il y a une erreur et implémenter l'exit
node_type dernier_type_rencontre;
const char * dernier_type_string;

bool decl, affect, init = false;
int offset_var = 0;
bool in_main = false;

void passe1(node_t node)
{
  node_nature nature = node->nature;
  yylineno = node->lineno;

  //Pour le debug
  const char * nature_string = node_nature2string(node->nature);

  node_nature nature1;
  const char * nature_string1;

  const char * type_string = node_type2string(node->type);
  node_type type1;
  node_type type2;
  node_type type3;
  const char * type_string1;
  const char * type_string2;
  const char * type_string3;
  int32_t offset_variable;
  char message[50];
  node_t node_temp;
  node_t node_temp2;
  node_t node_temp3;

  if(niveau_trace >= 3)
  {
    printf("\nJe suis dans le node : %s\n", nature_string);
    printf("Le type du node est : %s\n", type_string);
  }
  //printf("Le dernier node type rencontré est : %s\n", dernier_type_string);

  if(niveau_trace >= 4)
  {
    printf("Avant switch\n");
  }

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
      //Je mets à jour le champ type du node ident
      type1 = node->opr[0]->type; //Le type déclaré

      if(node->opr[0] != NULL && node->opr[1] != NULL && node->opr[1]->opr[0] != NULL && node->opr[1]->opr[1] != NULL)
      {

        if(node->opr[1]->nature == NODE_LIST)
        {
          node_Liste(node->opr[1], type1);
        }
        else
        {
          //Quand il y a NODE DECL IDENT INT/BOOLVAL

          type1 = node->opr[0]->type; //Le type déclaré
          type3 = node->opr[1]->opr[1]->type; //Le type réellement affecté
          node->opr[1]->opr[0]->type = type1; //Le type du NODE IDENT
          type2 = node->opr[1]->opr[0]->type;
          type_string1 = node_type2string(type1);
          type_string2 = node_type2string(type2);
          type_string3 = node_type2string(type3);

          if(niveau_trace >= 4)
          {
            printf("Type déclaré : %s\n", type_string1);
            printf("Type du NODE IDENT : %s\n", type_string2);
            printf("Type réellement affecté : %s\n", type_string3);
          }

          if(type1 != type3)
          {
            yyerror(&node, "Le type déclaré est différent du type affecté.");

          }
        }
      }
      else if(node->opr[0] != NULL && node->opr[1] != NULL)
      {                //Quand il y a NODE DECL IDENT INT/BOOLVAL

        type1 = node->opr[0]->type; //Le type déclaré
        node->opr[1]->type = type1;
        type2 = node->opr[1]->type ; //Le type du NODE IDENT
        type_string1 = node_type2string(type1);
        type_string2 = node_type2string(type2);

        if(niveau_trace >= 4)
        {
          printf("Type déclaré : %s\n", type_string1);
          printf("Type du NODE IDENT : %s\n", type_string2);
        }
      }


      //declaration sans initialisation
      if(node->opr[1]->nature == NODE_IDENT)
      {
          node_temp = node->opr[1];
          node->opr[1] = make_node(NODE_DECL, 2, TYPE_NONE, TYPE_NONE);
          node->opr[1]->opr[0] = node_temp;
          if(node->opr[0]->type == TYPE_INT)
          {
            node->opr[1]->opr[1] = make_node(NODE_INTVAL,0);
            node->opr[1]->opr[1]->value = 0;
          }
          else if(node->opr[0]->type == TYPE_BOOL)
          {
            node->opr[1]->opr[1] = make_node(NODE_BOOLVAL,0);
            node->opr[1]->opr[1]->value = 0;
          }
      }
      break;
    case NODE_DECL :
      if(niveau_trace >= 4)
      {
        printf("Déclaration de : %s\n", node->opr[0]->ident);
      }
      offset_variable = env_add_element(node->opr[0]->ident, node->opr[0], 4);

      if(offset_variable >= 0) //Première déclaration de la variable
      {
    	  node->opr[0]->offset = offset_var;
    	  offset_var = offset_var + 4;
    	  if(in_main)
    	  {
    	  	node->opr[0]->global_decl = false;
    	  }
      }
      else                     //Multiple déclaration de la variable
      {
        sprintf(message, "Multiple déclaration de '%s'", node->opr[0]->ident);
        yyerror(&node, message);
      }
      break;
    case NODE_IDENT :
      if (strcmp(node->ident,"main") == 0)
      {
	       in_main = true;
        //C'est le main
        //printf("\nJe suis là ?\n");

        if(node->type != TYPE_VOID)
        {
          yyerror(&node, "Le main n'est pas de type void.");
        }
      }
      else
      {
        node_t node_decl = (node_t)get_decl_node(node->ident);
        if (node_decl == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->ident);
          yyerror(&node, message);
        }
        else
        {
          node->decl_node = node_decl;
      	  node->offset = node_decl->offset;
          // node->type = node_decl->type;
      	  if(node_decl->global_decl == false)
      	  {
      	  	node->global_decl = false;
      	  }
        }
      }

      break;
    case NODE_AFFECT :

      if(node->opr[1]->nature == NODE_INTVAL)
      {
          type1 = node->opr[1]->type;
          node->type = type1;
      }
      else if(node->opr[1]->nature == NODE_BOOLVAL)
      {
          type1 = node->opr[1]->type;
          node->type = type1;
      }

      if(node->opr[0]->nature == NODE_IDENT)
      {
        node_temp = (node_t)get_decl_node(node->opr[0]->ident);

        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        type2 = node_temp->type;

        if((node->opr[1]->nature == NODE_INTVAL || node->opr[1]->nature == NODE_BOOLVAL) && node->opr[1]->type != type2)
        {
          yyerror(&node, "Les deux arguments ne sont pas de même type.");

        }
      }

      if(node->opr[1]->nature == NODE_IDENT)
      {
        node_temp = (node_t)get_decl_node(node->opr[1]->ident);

        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[1]->ident);
          yyerror(&node, message);
        }

        type1 = node_temp->type;

        if(type2 != type1)
        {
          yyerror(&node, "Les deux arguments ne sont pas de même type.");
        }
      }



      break;
    case NODE_TYPE :
      dernier_type_rencontre = node->type;
      dernier_type_string = node_type2string(dernier_type_rencontre);
      break;
    case NODE_INTVAL :
      break;
    case NODE_BOOLVAL :
      break;
    case NODE_STRINGVAL :
      node->offset = add_string(node->str); //ajoute la declaration en .data et retourne l'offset
      break;
    case NODE_FUNC :
      //A appeler au début de l'anamyse d'une fonction
      reset_env_current_offset(); //reset l'offset courant à 0
      reset_temporary_max_offset(); //reset l'offset maximum pour les temporaires
      set_max_registers(nb_registres); //définit le nombre maximal de registres à utiliser

      if(node->opr[0] != NULL && node->opr[1] != NULL)
      {
        type1 = node->opr[0]->type; //Le type déclaré
        node->opr[1]->type = type1;
        type2 = node->opr[1]->type ; //Le type du NODE IDENT
        type_string1 = node_type2string(type1);
        type_string2 = node_type2string(type2);

        if(niveau_trace >= 4)
        {
          printf("\nType déclaré : %s\n", type_string1);
          printf("Type du NODE IDENT : %s\n", type_string2);
        }
      }

      break;
    case NODE_IF :
    case NODE_WHILE :
      if (node->opr[0]->nature != NODE_IDENT && node->opr[0]->type != TYPE_BOOL)
      {
        yyerror(&node, "La condition n'est pas de type 'bool'.");
      }
      else if(node->opr[0]->nature == NODE_IDENT)
      {

        node_temp = (node_t)get_decl_node(node->opr[0]->ident);

        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        type2 = node_temp->type;

        if(type2 != TYPE_BOOL)
        {
          yyerror(&node, "La condition n'est pas de type 'bool'.");

        }
      }
      break;
    case NODE_FOR :
    case NODE_DOWHILE :
      if (node->opr[1]->nature != NODE_IDENT && node->opr[1]->type != TYPE_BOOL)
      {
        yyerror(&node, "La condition n'est pas de type 'bool'.");
      }
      else if(node->opr[1]->nature == NODE_IDENT)
      {

        node_temp = (node_t)get_decl_node(node->opr[1]->ident);

        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        type2 = node_temp->type;

        if(type2 != TYPE_BOOL)
        {
          yyerror(&node, "La condition n'est pas de type 'bool'.");

        }
      }
      break;
    // Opérations entre 1 ou 2 nombres, vérification du type des arguments
    case NODE_PLUS :
    case NODE_MINUS :
    case NODE_MUL :
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
    case NODE_EQ :
    case NODE_NE :

    	if(node->opr[0]->nature == NODE_IDENT)
    	{
    		node_temp = (node_t)get_decl_node(node->opr[0]->ident);
        // type_string2 = node_type2string(type2);
        // type_string3 = node_type2string(type3);
        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        // type_string1 = node_type2string(node_temp->type);
        // printf("Type observé : %s\n", type_string1);

        if(node_temp->type != TYPE_INT)
        {
          yyerror(&node, "Un des arguments n'est pas de type 'int'.");
        }
    	}
      else if(node->opr[0]->nature == NODE_BOOLVAL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'int'.");
      }

      if(node->opr[1]->nature == NODE_IDENT)
      {
        node_temp = (node_t)get_decl_node(node->opr[1]->ident);

        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[1]->ident);
          yyerror(&node, message);
        }

        if(node_temp->type != TYPE_INT)
        {

          yyerror(&node, "Un des arguments n'est pas de type 'int'.");
        }
      }
      else if(node->opr[1]->nature == NODE_BOOLVAL)
      {

        yyerror(&node, "Un des arguments n'est pas de type 'int'.");
      }

      break;
    case NODE_DIV :
    case NODE_MOD :
      if(node->opr[0]->nature == NODE_IDENT)
      {
        node_temp3 = (node_t)get_decl_node(node->opr[0]->ident);

        if (node_temp3 == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        if(node_temp3->type != TYPE_INT)
        {
          yyerror(&node, "Un des arguments n'est pas de type 'int'.");
        }
      }
      else if(node->opr[0]->nature == NODE_BOOLVAL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'int'.");
      }

      if(node->opr[1]->nature == NODE_IDENT)
      {
        node_temp2 = (node_t)get_decl_node(node->opr[1]->ident);


        if (node_temp2 == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[1]->ident);
          yyerror(&node, message);
        }
        if(node_temp2->type != TYPE_INT)
        {

          yyerror(&node, "Un des arguments n'est pas de type 'int'.");
        }
      }
      else if(node->opr[1]->nature == NODE_BOOLVAL)
      {

        yyerror(&node, "Un des arguments n'est pas de type 'int'.");
      }

      // if(node->opr[1]->value == 0)
      if(node->opr[1]->nature == NODE_INTVAL && node->opr[1]->value == 0 )
      {
        if(node->nature == NODE_DIV)
        {
          yyerror(&node, "La division par 0 n'est pas autorisée.");
        }
        else if(node->nature == NODE_MOD)
        {
          printf("%ld %ld\n", node_temp3->decl_node->value, node_temp2->value);
          sprintf(message, "'%ld mod 0' n'est pas défini.", node->opr[0]->value);
          yyerror(&node, message);
        }
      }

      break;
      // Opérations entre 1 ou 2 nombres qui retournent un entier, vérification du type des arguments
    case NODE_AND :
    case NODE_OR :
      if(node->opr[0]->nature == NODE_IDENT)
      {
        node_temp3 = (node_t)get_decl_node(node->opr[0]->ident);

        if (node_temp3 == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        if(node_temp3->type != TYPE_BOOL)
        {
          yyerror(&node, "Un des arguments n'est pas de type 'bool'.");
        }
      }
      else if(node->opr[0]->nature == NODE_INTVAL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'bool'.");
      }

      if(node->opr[1]->nature == NODE_IDENT)
      {
        node_temp2 = (node_t)get_decl_node(node->opr[1]->ident);


        if (node_temp2 == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[1]->ident);
          yyerror(&node, message);
        }
        if(node_temp2->type != TYPE_BOOL)
        {

          yyerror(&node, "Un des arguments n'est pas de type 'bool'.");
        }
        // if(node_temp->value == 0 )
      }
      else if(node->opr[1]->nature == NODE_INTVAL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'bool'.");
      }

      break;

    case NODE_NOT :

    if(node->opr[0]->nature == NODE_IDENT)
    {
      node_temp3 = (node_t)get_decl_node(node->opr[0]->ident);

      if (node_temp3 == NULL)
      {
        sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
        yyerror(&node, message);
      }

      if(node_temp3->type != TYPE_BOOL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'bool'.");
      }
    }
    else if(node->opr[0]->nature == NODE_INTVAL)
    {
      yyerror(&node, "Un des arguments n'est pas de type 'bool'.");
    }
      break;
    case NODE_BNOT :
    case NODE_UMINUS :

      if(node->opr[0]->nature == NODE_IDENT)
      {
        node_temp = (node_t)get_decl_node(node->opr[0]->ident);
        // type_string2 = node_type2string(type2);
        // type_string3 = node_type2string(type3);
        if (node_temp == NULL)
        {
          sprintf(message, "La variable '%s' n'est pas déclarée.", node->opr[0]->ident);
          yyerror(&node, message);
        }

        // type_string1 = node_type2string(node_temp->type);
        // printf("Type observé : %s\n", type_string1);

        if(node_temp->type != TYPE_INT)
        {
          yyerror(&node, "Un des arguments n'est pas de type 'int'.");
        }
      }
      else if(node->opr[0]->nature == NODE_BOOLVAL)
      {
        yyerror(&node, "Un des arguments n'est pas de type 'int'.");
      }

      break;
    case NODE_PRINT :
      node_Liste_print(node);
      break;
    default :
      yyerror(&node, "Nature du node non reconnue.");
      break;
  }

  if(niveau_trace >= 4)
  {
    printf("Après switch\n");
  }

  if(niveau_trace >= 3)
  {
    printf("Passe 1 sur les arguments\n");
  }

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
        if(niveau_trace >= 4)
        {
          printf("Noeud NULL\n");
        }
      }
    }
  }
  else
  {
    if(niveau_trace >= 4)
    {
      printf("Pas d'arguments\n");
    }
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
    default:
      break;
  }

}

void node_Liste(node_t node, node_type type)
{
  const char * type_string = node_type2string(type);

  if(niveau_trace >= 4)
  {
    printf("Type dans NODE LIST : %s\n", type_string);
  }

  node_nature nature;
  node_t opr0 = node->opr[0];
  node_t opr1 = node->opr[1];

  if(opr0->nature == NODE_LIST)
  {
    node_Liste(opr0, type);
  }
  else if(opr0->nature == NODE_IDENT)
  {
    opr0->type = type;
  }

  if(opr1->nature == NODE_LIST)
  {
    node_Liste(opr1, type);
  }
  else if(opr1->nature == NODE_IDENT)
  {
    opr1->type = type;
  }
}

void node_Liste_print(node_t node)
{
  /*
  if (node->opr[0] != NULL)
  {
    node_t opr0 = node->opr[0];

    if(opr0->nature == NODE_LIST)
    {
      node_Liste_print(opr0);
    }
  }
  if (node->opr[1] != NULL)
  {
    node_t opr1 = node->opr[1];

    if(opr1->nature == NODE_LIST)
    {
      node_Liste_print(opr1);
    }
  }

*/

}
