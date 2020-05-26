#include "passe2.h"

extern int niveau_trace;
bool end_of_tree = false;
bool is_global = true;
bool opening = true;
int offset_maxi = 0;
int offset_curr = 0;
bool verif = true;
int* str_offset = NULL;
int glob_str = 0;
int print_offset = 0;
int str_curr = 0;
int glob_int_counter = 0;

void generator(node_t nt)
{

	create_program();


	if(nt)
	{
		opening_closing_node(nt);
		next_node(nt);
		verif = false;
		str_curr = 0;
		is_global = true;
		opening = true;
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
	if(niveau_trace == 5)
	{
		printf("NEXT NODE\n");
		printf("NOPS = %d\n", nt->nops);
	}

	for(int n = 0; n < nt->nops; n++)
	{
		if(nt->opr[n] != NULL && ((nt->opr[n]->nature != NODE_IDENT || nt->opr[n]->nature != NODE_INTVAL) || (nt->opr[n]->nature == NODE_IDENT && nt->opr[n]->type == TYPE_VOID)))
		{
			opening = true;

			if(niveau_trace == 5)
			{
				printf("NODE OPENING\n");
			}

			opening_closing_node(nt->opr[n]);
			next_node(nt->opr[n]);
			opening = false;

			if(niveau_trace == 5)
			{
				printf("NODE CLOSING\n");
			}

			opening_closing_node(nt->opr[n]);
			}
	}
}


void opening_closing_node(node_t nt)
{
	if(opening)
	{
		if(niveau_trace == 5)
		{
			printf("\nNature du noeud détecté : %s\n", node_nature2string(nt->nature));
		}
		switch(nt->nature)
		{
			case NODE_PROGRAM:
				// Création du segment DATA
				if(verif)
				{
					create_data_sec_inst();
				}
				break;

			case NODE_FUNC:
				// Entrée dans le main
				gen_func(nt);
				break;


			case NODE_LIST:
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

			case NODE_PRINT:
				add_print(nt);
				break;
			
			case NODE_PLUS:
				add_arith_op(nt);

			default:
				break;
		}

	}

}

// Entrée dans le main
void gen_func(node_t nt)
{
	if(!verif)
	{
		// Création du segment TEXT
		create_text_sec_inst();
	}

	is_global = false;
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
				create_word_inst(nt->opr[0]->ident, nt->opr[1]->value);
				if(niveau_trace == 5)
				{
					printf("Création d'une nouvelle variable globale\n");
					printf(" IDENT : %s, VALUE : %ld\n", nt->opr[0]->ident, nt->opr[1]->value);
				}
				glob_int_counter++;
			}
			else if(nt->opr[1]->nature == NODE_IDENT)
			{
				create_word_inst(nt->opr[1]->ident, nt->opr[0]->value);
				glob_int_counter++;
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
					if(niveau_trace == 5)
					{
						printf("Création d'une nouvelle variable locale\n");
						printf(" IDENT : %s, VALUE : %ld\n", nt->opr[0]->ident, nt->opr[1]->value);
					}
					create_ori_inst(get_current_reg(), r0, nt->opr[1]->value);
					create_sw_inst(get_current_reg(), nt->opr[0]->offset, 29);
					offset_curr = offset_curr + 4;
				}
			}
			else if(nt->opr[1]->nature == NODE_IDENT)
			{
				if(verif)
				{
					offset_maxi = offset_maxi + 4;
				}
				else if(!verif)
				{
					create_ori_inst(get_current_reg(), r0, nt->opr[0]->value);
					create_sw_inst(get_current_reg(), nt->opr[1]->offset, 29);
					offset_curr = offset_curr + 4;
				}

			}
		}
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
			if(nt->type == TYPE_VOID) // Pour la declaration du main
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
	if(opening && !verif)
	{
		if(is_global)
		{
		
		}
		else
		{
			create_ori_inst(get_current_reg(), r0, nt->opr[1]->value);
			create_sw_inst(get_current_reg(), nt->opr[0]->offset, 29);
			
			if(niveau_trace == 5)
			{
				printf("%ld\n\n\n", nt->opr[1]->value);
			}
		}
	}


/*	else if(!opening && !verif)
	{
		if(is_global)
		{

		}
		else
		{
			//create_ori_inst(get_current_reg(), r0, nt->opr[1]->value);
			create_sw_inst(get_current_reg(), nt->opr[0]->offset, 29);
			if(niveau_trace == 5)
			{
				printf("%ld\n\n\n", nt->opr[1]->value);
			}
		}
	}
*/
}

void add_intval(node_t nt)
{

}


void add_stringval(node_t nt)
{

	if(verif && is_global)
	{
		create_asciiz_inst(create_labels_for_glob_str(glob_str), nt->str);
		glob_str = glob_str + 1;
	}

	if(verif && !is_global)
	{
		create_asciiz_inst(NULL, nt->str);
		str_offset = realloc(str_offset, sizeof(int));
		str_offset[str_curr] = strlen(nt->str) - 2;
		str_curr++;
	}
}

void add_print(node_t nt)
{
	if(!verif && opening)
	{
		if(nt->opr[0]->nature == NODE_STRINGVAL)
		{
			int str_offset_val = glob_int_counter * 4;
			for(int i = 0; i < str_curr; i++)
			{
				str_offset_val = str_offset_val + str_offset[i];
			}

			if(niveau_trace == 5)
			{
				printf("L'offset vaut : %d\n", str_offset_val);
			}

			create_lui_inst(4, 0x1001);
			create_ori_inst(4, 4, str_offset_val);
			create_ori_inst(2, r0, 4);
			create_syscall_inst();
			str_curr++;
		}

		else if(nt->opr[0]->nature == NODE_IDENT)
		{
			node_t node_decl = (node_t)get_decl_node(nt->opr[0]->ident);
			if(node_decl != NULL && node_decl->global_decl == true)
			{
				create_lui_inst(4, 0x1001);
				create_lw_inst(4, nt->opr[0]->offset, 4);
				create_ori_inst(2, r0, 1);
				create_syscall_inst();
			}
			else if(nt->opr[0]->global_decl == false)
			{
				create_lw_inst(4, nt->opr[0]->offset, 29);
				create_ori_inst(2, r0, 1);
				create_syscall_inst();
			}

		}
	}
}




void add_arith_op(node_t nt)
{
	int32_t reg0, reg1;

	if(!verif)
	{
		if(opening) 
		{// Cas où les opérandes sont soit une variable globale ou locale, soit des entiers immédiats
			if(nt->opr[0]->nature == NODE_INTVAL)
			{
				reg0 = get_current_reg();
				if(nt->opr[1]->nature == NODE_INTVAL)
				{// Cas avec 2 entiers immédiats
					create_ori_inst(reg0, r0, nt->opr[0]->value);
					allocate_reg();
					reg1 = get_current_reg();
					create_ori_inst(reg1, r0, nt->opr[1]->value);
					release_reg();
					select_arith_op(nt->nature, reg0, reg1);
				}
			}
		}
		
		else if(!opening) 
		{// Sinon il faut attendre la réduction des expressions en entier
			
		}  
	}
}



void select_arith_op(node_nature nature, int32_t reg0, int32_t reg1)
{
	switch(nature)
	{
		case NODE_PLUS:
			create_addu_inst(reg0, reg0, reg1);
			break;
	}
}





void add_type(node_t nt)
{

}






