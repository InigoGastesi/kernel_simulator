#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/process_queue_manager.h"
#include <pthread.h>

pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _PRO_GEN_MUTEX_COND = PTHREAD_COND_INITIALIZER;

pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _PRO_GEN_MUTEX = PTHREAD_MUTEX_INITIALIZER;


unsigned int _PID=0;
unsigned int _DONE=0;

int main(int argc, char *argv[]){
    pthread_t timerId, clockId, proGenId;
    process_queue *processQueue = malloc(sizeof(process_queue));
    pro_gen_args *proGenArgs = malloc(sizeof(pro_gen_args));

    proGenArgs->period=10;
    proGenArgs->processQueue=processQueue;

    unsigned int temp_kop = 1;
    if (argc ==2){
        temp_kop = atoi(argv[1]);
    }
    pthread_create(&proGenId, NULL, &process_generator, proGenArgs);
    pthread_create(&timerId, NULL, &start_timer, NULL);
    pthread_create(&clockId, NULL, &start_clock, (void*)temp_kop);
    pthread_join(clockId, NULL);
    return 0;
}