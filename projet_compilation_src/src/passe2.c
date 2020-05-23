#include "passe2.h"

bool end_of_tree = false;
bool is_global = true;
bool opening = 1;
int offset_maxi = 0;
int offset_curr = 0;
bool verif = 1;
int* str_offset = NULL;

void generator(node_t nt)
{
	printf("GENERATOR\n");
	create_program();


	if(nt)
	{	
		printf("NODE DETECTED\n");
		opening_closing_node(nt);
		next_node(nt);
		verif = 0;
		is_global = true;
		opening_closing_node(nt);
		next_node(nt);
		
	}

	create_addiu_inst(29, 29, offset_maxi);

	// Appel systeme 10 pour terminer le programme
	create_ori_inst(2, r0, 10);
	create_syscall_inst();
	
	dump_mips_program(outfile);
	free_program();
}


void next_node(node_t nt)
{
	printf("NEXT NODE\n");
	printf("NOPS = %d\n", nt->nops);
	for(int n = 0; n < nt->nops; n++)
	{
		if(nt->opr[n] != NULL && ((nt->opr[n]->nature != NODE_IDENT || nt->opr[n]->nature != NODE_INTVAL) || (nt->opr[n]->nature == NODE_IDENT && nt->opr[n]->type == TYPE_VOID)))
		{
			opening = true;
			printf("NODE OPEN\n");
			opening_closing_node(nt->opr[n]);
			next_node(nt->opr[n]);
			opening = false;
			printf("NODE CLOSE\n");
			opening_closing_node(nt->opr[n]);
			}
	}
}


void opening_closing_node(node_t nt)
{
	if(opening)
	{
		printf("NODE NATURE : %s\n", node_nature2string(nt->nature));
		switch(nt->nature)
		{
			case NODE_PROGRAM:
				// Création du segment DATA
				if(verif)
				{
					create_data_sec_inst();
				}
				//printf("NODE_PROGRAM\n");
				break;

			case NODE_FUNC:
				// Entrée dans le main
				//printf("NODE_FUNC\n");
				is_global = false;
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

			case NODE_STRINGVAL:
				add_stringval(nt);
				break;

			default:
				break;
		}

	}

}

// Entrée dans le main
void gen_func(node_t nt)
{
	if(opening && !verif && is_global)
	{
		printf("GEN_FUNC\n");
		is_global = false;
		int glob_str_nb = get_global_strings_number();

		for(int cpt = 0; cpt < glob_str_nb; ++cpt)
		{
			/* Déclaration de variable*/
			create_asciiz_inst(create_labels_for_glob_str(cpt), get_global_string(cpt));
		}
		// Création du segment TEXT
		create_text_sec_inst();
	}
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
	if(opening)
	{
		if(is_global && verif)
		{
			if(nt->opr[0]->nature == NODE_IDENT)
			{
				printf("CREATE_WORD CASE 1\n");
				create_word_inst(nt->opr[0]->ident, nt->opr[1]->value);
				printf(" IDENT : %s, VALUE : %d\n", nt->opr[0]->ident, nt->opr[1]->value);
			}
			else if(nt->opr[1]->nature == NODE_IDENT)
			{
				printf("CREATE_WORD CASE 2\n");
				create_word_inst(nt->opr[1]->ident, nt->opr[0]->value);
			}
		}

		else if(!is_global)
		{
			if(nt->opr[0]->nature == NODE_IDENT)
			{
				if(verif)
				{
					offset_maxi = offset_maxi + 4;
				}
				else if(!verif)
				{		
					create_ori_inst(get_current_reg(), r0, nt->opr[1]->value);
					create_sw_inst(get_current_reg(), 0, 29);
					offset_curr = offset_curr + 4;
				}
			}
			else if(nt->opr[1]->nature == NODE_IDENT)
			{
				
			}
		}
	}


	else
	{

	}

}

void add_ident(node_t nt)
{
	if(opening && !verif)
	{
		if(is_global)
		{

		}
		else
		{
			if(nt->type == TYPE_VOID)
			{
				create_label_str_inst(nt->ident);
				create_addiu_inst(29, 29, -offset_maxi);
			}
		}
	}


	else
	{

	}

}



void add_affect(node_t nt)
{
	if(opening)
	{
		if(is_global)
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


void add_stringval(node_t nt)
{
	if(verif && !is_global)
	{
		create_asciiz_inst(NULL, nt->str);
		str_offset = realloc(str_offset, strlen(nt->str) + 1);
	}
}

void add_type(node_t nt)
{

}
