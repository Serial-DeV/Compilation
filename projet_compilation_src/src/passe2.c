#include "passe2.h"

void generator(node_t nt)
{
	create_program();
	dump_mips_program(asm_file);

	if(nt)
	{
		while(!end)
		{
			after_node(nt);
		}
	}

	free_program();
}


void after_node(node_t nt)
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

		default:
			break;
	}
}


void gen_func(node_t nt)
{	char* label;
	int glob_str_nb = get_global_strings_number();
	for(int cpt = 0; cpt < glob_str_nb; ++cpt)
	{
		/* Déclaration de variable*/
		create_asciiz_inst(create_labels_for_glob_str(cpt), get_global_string(cpt));
	}
}




/* Création des labels pour les str en concaténant string_ et un entier, afin de distinguer les labels des variables*/
char* create_labels_for_glob_str(int cpt)
{	
	char* label;
	sprintf(label, "string_%d", cpt);
	return label;
}
