#include "../include/rb_tree_manager.h"

rb_tree* init_rb_tree(){
    rb_tree* tree = malloc(sizeof(rb_tree));
    return tree;
}

pcb* get_leftmost(rb_tree* tree){
    return tree->rb_leftmost;
}

void add_pcb_recursive(rb_node* node){
    if(node->left==NULL || node->right==NULL){
        rb_node* new_node=malloc(sizeof(rb_node));
    }
    else{

    }
}

void add_pcb(rb_tree* tree, pcb* process){
    if(tree->root == NULL){
        rb_node* new_node=malloc(sizeof(rb_node));
        new_node->process=process;
        tree->root=new_node;
    }
    else{
        add_pcb_recursive(tree->root);
    }
}

