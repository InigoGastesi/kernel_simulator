#ifndef _STRUCTS_H
#define _STRUCTS_H
#include <semaphore.h>
typedef struct pcb{
    struct pcb *prev;
    struct pcb *next;
    int pid;
    int state;
    int quantum;
    int initial_quantum;
    int counter;
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
    int last_pos;
} process_queue;

typedef struct pcb_list{
    struct pcb *first;
    struct pcb *last;
    int size;
} pcb_list;

typedef struct pro_gen_args{
    struct pcb_list *pcbList;
    struct process_queue *processQueue;
}pro_gen_args;

typedef struct timer_args{
    unsigned int period;
    char function;
    sem_t *sem;
}timer_args;

typedef struct clock_args{
    unsigned int timer_kop;
}clock_args;

typedef struct sche_args{
    struct machine *machine;
    struct process_queue *processQueue;
}sche_args;

typedef struct thread_args{
    unsigned int thread_id;
    unsigned int core_id;
    unsigned int cpu_id;
    struct pcb_list *pcbList;
    struct machine *machine;
    struct process_queue *processQueue;
    sem_t *sem;
}thread_args;

typedef struct thread{
    int id;
    struct pcb* process;
} thread;

typedef struct core{
    struct thread** threads;
    int id;
    int number_of_threads;
} core;

typedef struct cpu{
    struct core** cores;
    int id;
    int number_of_cores;
} cpu;

typedef struct machine{
    struct cpu** cpus;
    int number_of_cpus;
} machine;

#endif