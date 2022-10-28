#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/process_queue_manager.h"
#include "../include/schedule.h"
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _PRO_GEN_MUTEX_COND = PTHREAD_COND_INITIALIZER;

pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _PRO_GEN_MUTEX = PTHREAD_MUTEX_INITIALIZER;

sem_t _PRO_GEN_SEM;
sem_t _SCHE_SEM;


unsigned int _PID=0;
unsigned int _DONE=0;

int main(int argc, char **argv){
    pthread_t timerProGenId, timerScheId, clockId, proGenId, scheId;
    process_queue *processQueue = malloc(sizeof(process_queue));
    pro_gen_args *proGenArgs = malloc(sizeof(pro_gen_args));
    timer_args *timerProGenArgs = malloc(sizeof(timer_args));
    timer_args *timerScheArgs = malloc(sizeof(timer_args));
    clock_args *clockArgs = malloc(sizeof(clock_args));

    sem_init(&_PRO_GEN_SEM, 0 ,0);
    sem_init(&_SCHE_SEM, 0, 0);
    
    proGenArgs->processQueue=processQueue;
    timerProGenArgs->period=1000;
    timerProGenArgs->function='p';
    timerScheArgs->period=1000;
    timerScheArgs->function='s';
    clockArgs->timer_kop=2;
    int opt;
    while((opt = getopt(argc, argv, ":hp:s:")) != -1){
        switch (opt){
            case 'p':
                timerProGenArgs->period=atoi(optarg);
                printf("p argumentua %s\n", optarg);
                break;
            case 's':
                timerScheArgs->period=atoi(optarg);
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
            s: schedule-aren periodoa: %d\n",timerProGenArgs->period,timerScheArgs->period);

    sleep (3);


    proGenArgs->processQueue=processQueue;
    pthread_create(&proGenId, NULL, &process_generator, proGenArgs);
    pthread_create(&scheId, NULL, &schedule, NULL);
    pthread_create(&timerProGenId, NULL, &start_timer, timerProGenArgs);
    pthread_create(&timerScheId, NULL, &start_timer, timerScheArgs);
    pthread_create(&clockId, NULL, &start_clock, clockArgs);
    pthread_join(clockId, NULL);
    return 0;
}