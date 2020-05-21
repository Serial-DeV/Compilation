#include "passe2.h"

void generator(node_t nt)
{
	create_program();
	dump_mips_program(asm_file);

	if(nt)
	{
		//create_data_sec_inst();


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
{
	
}
