#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "structs.h"
#include <pthread.h>
extern pthread_mutex_t _CLOCK_MUTEX;
extern pthread_mutex_t _PRO_GEN_MUTEX;

extern pthread_cond_t _CLOCK_MUTEX_COND;
extern pthread_cond_t _TIMER_MUTEX_COND;
extern pthread_cond_t _PRO_GEN_MUTEX_COND;
#endif