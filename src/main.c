#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/pcb_list_manager.h"
#include "../include/schedule.h"
#include "../include/pcb_queue_manager.h"
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;

pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _PRO_GEN_MUTEX = PTHREAD_MUTEX_INITIALIZER;

sem_t _PRO_GEN_SEM;
sem_t _SCHE_SEM;


unsigned int _PID=0;
unsigned int _DONE=0;

int main(int argc, char **argv){
    pthread_t timerProGenId, timerScheId, clockId, proGenId, scheId;
    pcb_list *pcbList = malloc(sizeof(pcb_list));
    pro_gen_args *proGenArgs = malloc(sizeof(pro_gen_args));
    timer_args *timerProGenArgs = malloc(sizeof(timer_args));
    timer_args *timerScheArgs = malloc(sizeof(timer_args));
    clock_args *clockArgs = malloc(sizeof(clock_args));
    process_queue *processQueue = malloc(sizeof(process_queue));
    processQueue->queue=malloc(100*sizeof(pcb*));
    processQueue->size = 100;
    

    sem_init(&_PRO_GEN_SEM, 0 ,0);
    sem_init(&_SCHE_SEM, 0, 0);
    
    proGenArgs->pcbList=pcbList;
    timerProGenArgs->period=10000;
    timerProGenArgs->function='p';
    timerScheArgs->period=10000;
    timerScheArgs->function='s';
    clockArgs->timer_kop=2;
    int opt;
    while((opt = getopt(argc, argv, ":hp:s:")) != -1){
        switch (opt){
            case 'p':
                timerProGenArgs->period=atoi(optarg);
                break;
            case 's':
                timerScheArgs->period=atoi(optarg);
                break;
            case 'q':
                free(processQueue->queue);
                processQueue->queue = malloc(atoi(optarg)*sizeof(pcb*));
                processQueue->size = atoi(optarg);
                break;
            case 'h':
                printf("\t[-p][process generator-en periodoa]\n\t[-t][timer kopurua]\n");
                exit(0);
                break;
            case ':':
                printf("option needs a value\n");
                exit(0);
                break;
            case '?':
                printf("\t[-p][process generator-en periodoa]\n\t[-t][timer kopurua]\n");
                exit(0);
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


    proGenArgs->pcbList=pcbList;
    pthread_create(&proGenId, NULL, &process_generator, proGenArgs);
    pthread_create(&scheId, NULL, &schedule, NULL);
    pthread_create(&timerProGenId, NULL, &start_timer, timerProGenArgs);
    pthread_create(&timerScheId, NULL, &start_timer, timerScheArgs);
    pthread_create(&clockId, NULL, &start_clock, clockArgs);
    pthread_join(clockId, NULL);
    return 0;
}