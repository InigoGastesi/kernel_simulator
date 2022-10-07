#ifndef _STRUCTS_H
#define _STRUCTS_H
typedef struct process{
    struct process *prev;
    struct process *next;
    int pid;
} process;

typedef struct pcb{
    struct process *first;
    struct process *last;
} pcb;

typedef struct pro_gen_args_structs{
    unsigned int period;
    struct pcb *procces_control;
}pro_gen_args;
#endif