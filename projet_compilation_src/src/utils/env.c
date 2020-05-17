#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <getopt.h>

#include "context.h"
#include "env.h"

env_t env; //Contexte courant déclaré en variable globale

void push_global_context()
{
  //Ceci est le context global
  context_t context = create_context();
  env = malloc(sizeof(env_s));
  env->context = context;
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

void * get_decl_node(char * ident);
int32_t env_add_element(char * ident, void * node, int32_t size);
void reset_env_current_offset();
int32_t get_env_current_offset();
int32_t add_string(char * str);
int32_t get_global_strings_number();
char * get_global_string(int32_t index);
void free_global_strings();
