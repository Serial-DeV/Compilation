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

context_t create_context()
{
	context_t context = malloc(sizeof(context_s));
	context->root = malloc(sizeof(noeud_s));
	context->root->idf_existant = false;
	return context;
}


void free_context(context_t context)
{
	free(context->root);
	free(context);
}


bool context_add_element(context_t context, char * idf, void * data)
{
	int taille = strlen(idf);
	int i = 0;
	noeud_t noeud_temp = context->root;

	for (i = 0; i < taille; i++)
	{
		//On parcourt l'arbre représenté par une liste chaînée en utilisant suite idf et on compare à l'argument idf
		noeud_temp = noeud_temp->suite_idf[idf[i] - 65]; //On prend A comme indice 0
		//Si l'idf est déjà présent, cela ne change rien
		noeud_temp->lettre = idf[i];
		noeud_temp->idf_existant = true;

	}

	//Si la dernière lettre de l'idf est déjà présente, il n'est donc pas nécessaire de l'ajouter
	if(noeud_temp->idf_existant)
	{
		printf("idf déjà présent");
		return false;
	}

	noeud_temp->data = data;

	return true;
}

void * get_data(context_t context, char * idf)
{
	int taille = strlen(idf);
	void * data;
	int i = 0;
	noeud_t noeud_temp = context->root;

	for (i = 0; i < taille; i++)
	{
		if(!(noeud_temp->idf_existant))
		{
			printf("Il n'y a pas d'idf correspondant");
			return NULL;
		}
		//On parcourt l'arbre représenté par une liste chaînée en utilisant suite idf et on compare à l'argument idf
		noeud_temp = noeud_temp->suite_idf[idf[i] - 65]; //On prend A comme indice 0 de la chaine
		if (noeud_temp == NULL)
		{
			printf("Ce noeud n'existe pas");
			return NULL;
		}
	}

	//Si on arrive ici, idf est déclaré
	
	data = noeud_temp->data;

	if (data == NULL)
	{
		printf("idf déclaré mais non initialisé");
	}
	return data;
}
