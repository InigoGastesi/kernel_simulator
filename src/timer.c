#include "../include/timer.h"
#include <pthread.h>

// unsigned int _CLOCK;
// pthread_mutex_t _CLOCK_MUTEX;
pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
void* start_timer(void * args){

    while (1){
        pthread_mutex_lock(&_CLOCK_MUTEX);

        pthread_cond_wait(&_CLOCK_MUTEX_COND, &_CLOCK_MUTEX);
        
        printf("tick\n");
        pthread_cond_signal(&_TIMER_MUTEX_COND);
        pthread_mutex_unlock(&_CLOCK_MUTEX);
        
    }

}