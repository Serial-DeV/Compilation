#include "env.h"

extern env_t env; //Contexte courant déclaré en variable globale


void push_global_context()
{
  //Ceci est le context global
  context_t context = create_context();
  env = malloc(sizeof(env_s));
  env->context = context;
  env->next = NULL;
}


void push_context()
{
  //Ce n'est pas le contexte global, on le relie donc au contexte global
  context_t context = create_context();
  env_t env_temp = malloc(sizeof(env_s));
  env_temp->context = context;
  env_temp->next = env; //si l'on sort de ce contexte on retourne au contexte global
  env = env_temp; //le nouveau contexte courant
}


void pop_context(env_t env_temp)
{
  env = env_temp->next; //On repasse au contexte précédent
  free(env_temp->context);
  free(env_temp);
}

//A modifier
/*
void * get_decl_noeud(char * ident)
{
  int taille = strlen(ident);
  noeud_t noeud = NULL;
  int i = 0;
  env_t env_temp = env; //On commence par le contexte actuel
  noeud_t noeud_temp = env_temp->context->root;

  while(env_temp != NULL || noeud != NULL) //Tant que nous ne sommes pas dans le contexte global ou que nous n'avons pas trouvé le noeud
  {
    for (i = 0; i < taille; i++)
    {
      if(!(noeud_temp->idf_existant))
      {
        printf("Il n'y a pas d'idf correspondant");
        i = taille + 1; //Permet de sortir de la boucle et de vérifier ensuite la raison de cette sortie
      }
      //On parcourt l'arbre représenté par une liste chaînée en utilisant suite idf et on compare à l'argument idf
      noeud_temp = noeud_temp->suite_idf[ident[i] - 65]; //On prend A comme indice 0 de la chaine
      if (noeud_temp == NULL)
      {
        printf("Ce noeud n'existe pas");
        i = taille + 1;
      }
    }
    //Si on arrive ici, idf est déclaré ou on doit passer à l'env suivant
    if (i > taille) //environnement suivant
    {
      env_temp = env_temp->next; //on cherche dans l'environnement suivant
      noeud_temp = env_temp->context->root;
    }
    else
    {
      noeud = noeud_temp;
      return noeud;
    }
  }

  if (noeud == NULL)
  {
    printf("Il n'y a pas de noeud correspondant");
    return noeud;
  }
  if (env_temp == NULL)
  {
    printf("Tous les environnements ont été parcouru sans succès");
    return noeud;
  }
  return noeud;
}
*/
int32_t env_add_element(char * ident, void * noeud, int32_t size);

void reset_env_current_offset();

int32_t get_env_current_offset();

int32_t add_string(char * str);

int32_t get_global_strings_number();

char * get_global_string(int32_t index);

void free_global_strings();
