#ifndef _STRUCTS_H
#define _STRUCTS_H
typedef struct pcb{
    struct pcb *prev;
    struct pcb *next;
    int pid;
} pcb;

typedef struct process_queue{
    struct pcb *first;
    struct pcb *last;
} process_queue;

typedef struct pro_gen_args{
    unsigned int period;
    struct process_queue *process_control;
}pro_gen_args;
#endif