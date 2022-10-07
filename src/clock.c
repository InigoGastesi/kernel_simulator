#include "../include/clock.h"
#include <pthread.h>

void * start_clock(void* args){
    unsigned int period = (unsigned int)args;
    unsigned int clock = 0;
    while (1)
    {
        pthread_mutex_lock(&_CLOCK_MUTEX);
        while (clock < period){
            clock++;
        }
        clock=0;
        pthread_cond_signal(&_CLOCK_MUTEX_COND);
        pthread_cond_wait(&_TIMER_MUTEX_COND, &_CLOCK_MUTEX);
        pthread_mutex_unlock(&_CLOCK_MUTEX);
    }
    
}