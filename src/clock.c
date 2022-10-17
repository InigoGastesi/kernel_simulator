#include "../include/clock.h"
#include <pthread.h>

void * start_clock(void* args){
    unsigned int temp_kop = (unsigned int)args;
    unsigned int clock = 0;
    while (1)
    {
        pthread_mutex_lock(&_CLOCK_MUTEX);
        while (_DONE < temp_kop){
            pthread_cond_wait(&_TIMER_MUTEX_COND, &_CLOCK_MUTEX);
        }
        _DONE=0;
        pthread_cond_broadcast(&_CLOCK_MUTEX_COND);
        pthread_mutex_unlock(&_CLOCK_MUTEX);
    }
}