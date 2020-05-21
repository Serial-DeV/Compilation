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
#include "defs.h"
#include "common.h"
#include "utils/context.h"
#include "utils/env.h"
#include "utils/registers.h"

char* asm_file;
bool end = false;
bool in_main = false;
bool global = true;


void generator(node_t);
void after_node(node_t);

#endif
