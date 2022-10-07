#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/process_generator.h"
#include <pthread.h>

pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _PRO_GEN_MUTEX = PTHREAD_MUTEX_INITIALIZER;



int main(int argc, char *argv[]){
    pthread_t timerId, clockId, proGenId;
    process_queue *process_control = malloc(sizeof(process_queue));
    pro_gen_args *proGenArgs = malloc(sizeof(pro_gen_args));
    proGenArgs->period=10;
    proGenArgs->process_control=process_control;
    int period = 100000;
    if (argc ==2){
        period = atoi(argv[1]);
    }
    pthread_create(&proGenId, NULL, &process_generator, (void*)&proGenArgs);
    pthread_create(&timerId, NULL, &start_timer, NULL);
    pthread_create(&clockId, NULL, &start_clock, (void*)period);
    pthread_join(clockId, NULL);
    return 0;
}