#include "../include/clock.h"
#include <pthread.h>

unsigned int _CLOCK = 0;
pthread_mutex_t _CLOCK_MUTEX;
void * start_clock(void* args){
    while (1)
    {
        pthread_mutex_lock(&_CLOCK_MUTEX);
        _CLOCK++;
        pthread_mutex_unlock(&_CLOCK_MUTEX);
    }
    
}