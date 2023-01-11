#ifndef _pcb_list_h
#define _pcb_list_h
#include "globals.h"
#include "structs.h"
#include "process_queue_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
void *process_generator(void * args);
void add_pcb(pcb_list *pcbList, process_queue *processQueue);
void print_pcbList(pcb_list *pcbList);
void delete_pcb(pcb *process, pcb_list *pcbList);
#endif