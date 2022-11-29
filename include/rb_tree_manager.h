#ifndef _RB_TREE_MANAGER
#define _RB_TREE_MANAGER

#include "structs.h"
#include "stdlib.h"

rb_tree* init_rb_tree();
pcb* get_leftmost(rb_tree* tree);
void add_pcb(rb_tree* tree, pcb* process);

#endif