#include "*.h"
#include "utils/*.h"


char* asm_file;
bool end = false;
bool in_main = false;
bool global = true;


void generator(node_t);
void after_node(node_t);
