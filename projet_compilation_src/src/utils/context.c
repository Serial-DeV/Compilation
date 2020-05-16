#include <context.h>

context_t create_context()
{
	context_t ct = malloc(sizeoff(context_t));
}


void free_context(context_t context)
{
	free(context);
}


bool context_add_element(context_t context, char * idf, void * data)
{
	if(context->root->idf_existant)
	{
		return false;
	}

	context->root->idf_existant = true;
	//context->root->lettre = idf;
	context->root->data = data;
	
	return true;
}


void * get_data(context_t context, char * idf)
{
	if(!context->root->idf_existant)
	{
		return NULL;
	}

	return context->root->data;
}
