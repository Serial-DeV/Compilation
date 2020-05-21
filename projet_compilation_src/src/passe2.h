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
bool end = false;
//bool in_main = false;
bool global = true;
bool open = 1;


void generator(node_t);
void open_close_node(node_t);
void gen_func(node_t);
char* create_labels_for_glob_str(int);
void add_decl(node_t);
void add_type(node_t);
void add_ident(node_t);
void add_intval(node_t);
void add_affect(node_t);

#endif
