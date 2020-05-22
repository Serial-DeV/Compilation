#include "passe2.h"

void generator(node_t nt)
{
	create_program();
	dump_mips_program(outfile);

	if(nt)
	{
		open_close_node(nt);
	}

	free_program();
}


void next_node(node_t nt)
{
	for(int n = 0; n < nt->nops; n++)
	{
		open = true;
		open_close_node(nt->opr[n]);
		next_node(nt);
		open = false;
		open_close_node(nt->opr[n]);
	}
}


void open_close_node(node_t nt)
{
	if(nt)
	{
		switch(nt->nature)
		{
			case NODE_PROGRAM:
				// Création du segment DATA
				create_data_sec_inst();
				break;

			case NODE_FUNC:
				// Entrée dans le main
				global = false;
				gen_func(nt);
				break;


			case NODE_LIST:
				break;

				case NODE_DECLS:
				// Ne rien faire de particulier
				break;

			case NODE_DECL:
				add_decl(nt);
				break;

			case NODE_TYPE:
				add_type(nt);
				break;

			case NODE_IDENT:
				add_ident(nt);
				break;

			case NODE_AFFECT:
				add_affect(nt);
				break;

			case NODE_INTVAL:
				add_intval(nt);
				break;

			default:
				break;
		}

	}
}

// Entrée dans le main
void gen_func(node_t nt)
{
	global = false;
	int glob_str_nb = get_global_strings_number();

	for(int cpt = 0; cpt < glob_str_nb; ++cpt)
	{
		/* Déclaration de variable*/
		create_asciiz_inst(create_labels_for_glob_str(cpt), get_global_string(cpt));
	}
	// Création du segment TEXT
	create_text_sec_inst();
}




/* Création des labels pour les str en concaténant string_ et la valeur du compteur */
char* create_labels_for_glob_str(int cpt)
{
	char* label;
	sprintf(label, "string_%d", cpt);
	return label;
}

void add_decl(node_t nt)
{
	if(open)
	{
		if(global)
		{
			if(nt->opr[1]->nature == NODE_IDENT);
		}
	}


	else
	{

	}

}

void add_ident(node_t nt)
{
	if(open)
	{
		if(global)
		{

		}
	}


	else
	{

	}

}



void add_affect(node_t nt)
{
	if(open)
	{
		if(global)
		{

		}
	}


	else
	{

	}

}

void add_intval(node_t nt)
{

}

void add_type(node_t nt)
{

}
