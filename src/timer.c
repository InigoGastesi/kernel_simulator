#include "../include/timer.h"
#include <pthread.h>

// unsigned int _CLOCK;
// pthread_mutex_t _CLOCK_MUTEX;


void* start_timer(void * args){
    timer_args* arguments = (timer_args *)args;
    unsigned int counter=0;
    unsigned int period = arguments->period;
    pthread_mutex_lock(&_CLOCK_MUTEX);
    while (1){
        
        _DONE++;
        counter++;
        //process generator
        
        if(counter > period){
            printf("tick %d\n", counter);
            pthread_cond_signal(&_PRO_GEN_MUTEX_COND);
            counter = 0;
        }
        pthread_cond_signal(&_TIMER_MUTEX_COND);
        pthread_cond_wait(&_CLOCK_MUTEX_COND, &_CLOCK_MUTEX);
    }
}