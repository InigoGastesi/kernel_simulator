#ifndef _STRUCTS_H
#define _STRUCTS_H
typedef struct pcb{
    struct pcb *prev;
    struct pcb *next;
    int pid;
    int state;
    int priority;
} pcb;

typedef struct rb_node{
    pcb* process;
    struct rb_node* parent;
    struct rb_node* left;
    struct rb_node* right;
}rb_node;

typedef struct rb_tree{
    rb_node* root;
    rb_node* rb_leftmost;
}rb_tree;


typedef struct process_queue{
    pcb** queue;
    int size;
    int first_free_position;
} process_queue;

typedef struct pcb_list{
    struct pcb *first;
    struct pcb *last;
} pcb_list;

typedef struct pro_gen_args{
    struct pcb_list *pcbList;
}pro_gen_args;

typedef struct timer_args{
    unsigned int period;
    char function;
}timer_args;

typedef struct clock_args{
    unsigned int timer_kop;
}clock_args;

typedef struct thread{
    int id;
    struct pcb* process;
} thread;

typedef struct core{
    struct thread* threads;
    int id;
} core;

typedef struct cpu{
    struct core* cores;
    int id;
} cpu;

typedef struct machine{
    struct cpu* cpus;
} machine;

#endif