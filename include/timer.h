#ifndef _TIMER_H
#define _TIMER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "globals.h"
#include "structs.h"
void* start_timer(void * args);
#endif