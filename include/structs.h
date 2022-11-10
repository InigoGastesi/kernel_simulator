#ifndef _STRUCTS_H
#define _STRUCTS_H
typedef struct pcb{
    struct pcb *prev;
    struct pcb *next;
    int pid;
} pcb;


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