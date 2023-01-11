#ifndef _PROCESS_QUEUE_MANAGER_H
#define _PROCESS_QUEUE_MANAGER_H
#include "../include/structs.h"
#include "stdlib.h"
#include "stdio.h"
#include "globals.h"
process_queue * init_queue(int size);
void push_queue(process_queue *processQueue, pcb* process);
pcb *pop_queue(process_queue *processQueue);
void print_queue(process_queue *processQueue);
#endif