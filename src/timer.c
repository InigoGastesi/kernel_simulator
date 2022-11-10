#include "../include/timer.h"

// unsigned int _CLOCK;
// pthread_mutex_t _CLOCK_MUTEX;

/**
 * @brief timera hasieratzen da eta funtzionantzen hasten da.
 * @param pro_gen_args timeraren periodoa eta 
 * @return void
 */
void* start_timer(void * args){
    //argumentuak jaso
    timer_args *arguments = (timer_args *)args;
    unsigned int counter=0;
    unsigned int period = arguments->period;
    char function = arguments->function;
    sem_t *sem;
    //pcb_list edo schedule-aren semaforoa hautatu
    switch (function){
        case 'p':
            sem = &_PRO_GEN_SEM;
            break;
        case 's':
            sem = &_SCHE_SEM;
            break;
        default:
            break;
    }
    pthread_mutex_lock(&_CLOCK_MUTEX);
    while (1){
        counter++;
        if(counter > period){
            //seinalea bidali funtzionalitateari
            sem_post(sem);
            counter = 0;
        }
        _DONE++;
        pthread_cond_signal(&_TIMER_MUTEX_COND);
        pthread_cond_wait(&_CLOCK_MUTEX_COND, &_CLOCK_MUTEX);
    }
}