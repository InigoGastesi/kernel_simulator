#include "../include/clock.h"
#include <pthread.h>

unsigned int _CLOCK = 0;
pthread_mutex_t clock_mutex;
void * start_clock(void* args){
    
    while (1)
    {
        pthread_mutex_lock(&clock_mutex);
        _CLOCK++;
        pthread_mutex_unlock(&clock_mutex);
    }
    
}