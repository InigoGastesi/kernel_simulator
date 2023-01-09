#include "../include/rb_tree_manager.h"

rb_tree* init_rb_tree(){
    rb_tree* tree = malloc(sizeof(rb_tree));
    return tree;
}

pcb* get_leftmost(rb_tree* tree){
    rb_node* leftmost = tree->rb_leftmost;
    rb_node* parent = leftmost->parent;
    if (parent->left == NULL){
        parent->right = NULL;
        tree->rb_leftmost = parent;
    }
    else{
        parent->left = NULL;
        tree->rb_leftmost = parent->right;
    }
    
    return leftmost;
}

void add_pcb_recursive(rb_node* node, pcb* process, rb_tree* tree){
    if(node->left==NULL || node->right==NULL){
        rb_node* new_node=malloc(sizeof(rb_node));
        new_node->process = process;
        new_node->parent = node;
        if (process->priority < node->process->priority){
            node->left = new_node;
        }
        else{
            node->right = new_node;
        }
        if(new_node->process->priority < tree->rb_leftmost->process->priority){
            tree->rb_leftmost = new_node;
        }
    }
    else if(node->process->priority <= process->priority){
        add_pcb_recursive(node->left, process, tree);
    }
    else if(node->process->priority > process->priority){
        add_pcb_recursive(node->right, process, tree);
    }
}

void add_pcb_tree(rb_tree* tree, pcb* process){
    if(tree->root == NULL){
        rb_node* new_node=malloc(sizeof(rb_node));
        new_node->process=process;
        tree->root=new_node;
    }
    else{
        add_pcb_recursive(tree->root, process, tree);
    }
}

