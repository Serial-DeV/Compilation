#ifndef _PASSE2_H_
#define _PASSE2_H_
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
#include "defs.h"
#include "common.h"
#include "utils/env.h"
#include "utils/registers.h"
#include "utils/mips_inst.h"

char* asm_file;
extern char * outfile;


void generator(node_t);
void opening_closing_node(node_t);
void next_node(node_t);
void gen_func(node_t);
char* create_labels_for_glob_str(int);
void add_decl(node_t);
void add_type(node_t);
void add_ident(node_t);
void add_intval(node_t);
void add_stringval(node_t);
void add_affect(node_t);
void add_print(node_t);
void add_arith_op(node_t);
void suite_arith_op(node_nature, int32_t, int32_t);

#endif
