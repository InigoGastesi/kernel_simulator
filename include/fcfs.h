#ifndef _FCFS_H
#define _FCFS_H
#include "../include/structs.h"
#include "stdlib.h"
#include "stdio.h"
process_queue * init_queue(int size);
void push_queue(process_queue *fcfs, pcb* process);
pcb *pop_queue(process_queue *fcfs);
#endif