#ifndef _PROCESS_QUEUE_h
#define _PROCESS_QUEUE_h
#include "globals.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *process_generator(void * args);
void add_pcb(process_queue *processQueue);
#endif