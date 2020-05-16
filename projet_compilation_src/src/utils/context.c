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
	if(context->idf_existant)
	{
		return false;
	}

	context->idf_existant = true;
	context->lettre = idf;
	context->data = data;
	
	return true;
}


void * get_data(context_t context, char * idf)
{
	if(!context->idf_existant)
	{
		return NULL;
	}

	return context->data;
}
