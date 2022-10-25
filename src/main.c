#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/process_queue_manager.h"
#include <pthread.h>

pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _PRO_GEN_MUTEX_COND = PTHREAD_COND_INITIALIZER;

pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _PRO_GEN_MUTEX = PTHREAD_MUTEX_INITIALIZER;

sem_t _PRO_GEN_SEM;


unsigned int _PID=0;
unsigned int _DONE=0;

int main(int argc, char *argv[]){
    pthread_t timerId, clockId, proGenId;
    process_queue *processQueue = malloc(sizeof(process_queue));
    pro_gen_args *proGenArgs = malloc(sizeof(pro_gen_args));
    timer_args *timerArgs = malloc(sizeof(timer_args));
    clock_args *clockArgs = malloc(sizeof(clock_args));
    sem_init(&_PRO_GEN_SEM, 0, 1);
    proGenArgs->processQueue=processQueue;
    proGenArgs->period=10;
    timerArgs->period=100000;
    clockArgs->timer_kop=1;
    int opt;

    while(opt = getopt(argc, argv, "hp:t:c:") != -1){
        switch (opt){
            case 'p':
                proGenArgs->period=atoi(optarg);
                printf("p argumentua %s\n", optarg);
                break;
            case 't':
                clockArgs->timer_kop=atoi(optarg);
                break;
            case 'c':
                timerArgs->period=atoi(optarg);
                break;
            case 'h':
                printf("\tp: process generator-en periodoa\n\tt: timer kopurua\n\tc: erlojuaren periodoa\n");
                exit(0);
                break;
            case ':':
                printf("option needs a value\n"); 
                break; 
        }
    }
    for (int i = optind; i < argc; i++){
        printf ("\tNon-option argument %s\n", argv[i]);
    }

    printf("\tAukeratutako argumentuak:\n\
            p: process generator-en periodoa: %d\n\
            t: timer kopurua: %d\n\
            c: erlojuaren periodoa: %d\n",proGenArgs->period,clockArgs->timer_kop,timerArgs->period);

    sleep (5);


    proGenArgs->processQueue=processQueue;
    pthread_create(&proGenId, NULL, &process_generator, proGenArgs);
    pthread_create(&timerId, NULL, &start_timer, timerArgs);
    pthread_create(&clockId, NULL, &start_clock, clockArgs);
    pthread_join(clockId, NULL);
    return 0;
}