#ifndef _pcb_list_h
#define _pcb_list_h
#include "globals.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
void *process_generator(void * args);
void add_pcb(pcb_list *pcbList);
void print_pcbList(pcb_list *pcbList);
#endif