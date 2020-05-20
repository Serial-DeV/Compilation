#ifndef _PASSE1_H_
#define _PASSE1_H_
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

extern void yyerror(node_t * program_root, char * s);
extern int yylineno;
extern env_t env;
extern int offset;
extern int32_t nb_registres;
void passe1(node_t node);

#endif
