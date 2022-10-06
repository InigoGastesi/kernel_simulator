#include "../include/timer.h"
#include <pthread.h>

// unsigned int _CLOCK;
// pthread_mutex_t _CLOCK_MUTEX;
void* start_timer(void * args){

    unsigned int frequency = (int)args;
    while (1){
        pthread_mutex_lock(&_CLOCK_MUTEX);
        if(_CLOCK < frequency){
            pthread_mutex_unlock(&_CLOCK_MUTEX);
            continue;
        }
        else{
            _CLOCK = 0;
            printf("%d\n",frequency);
            pthread_mutex_unlock(&_CLOCK_MUTEX);
        }
    }

}