#include "../include/clock.h"
#include "../include/timer.h"
#include "../include/pcb_list_manager.h"
#include "../include/schedule.h"
#include "../include/fcfs.h"
#include "../include/machine.h"
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_cond_t _CLOCK_MUTEX_COND = PTHREAD_COND_INITIALIZER;
pthread_cond_t _TIMER_MUTEX_COND = PTHREAD_COND_INITIALIZER;

pthread_mutex_t _CLOCK_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _PRO_GEN_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _SCHE_MUTEX = PTHREAD_MUTEX_INITIALIZER;

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
    sche_args *scheArgs = malloc(sizeof(sche_args));
    thread_args *threadArgs;
    process_queue *fcfs = init_queue(10);
    machine *machine = malloc(sizeof(machine));
    int number_of_cpus = 1;
    int number_of_cores = 1;
    int number_of_threads = 2;
    

    sem_init(&_PRO_GEN_SEM, 0 ,0);
    sem_init(&_SCHE_SEM, 0, 0);
    
    proGenArgs->pcbList=pcbList;
    timerProGenArgs->period=1000;
    timerProGenArgs->function='p';
    timerScheArgs->period=10000;
    timerScheArgs->function='s';
    clockArgs->timer_kop=2;
    int opt;
    while((opt = getopt(argc, argv, ":hp:s:q:")) != -1){
        switch (opt){
            case 'p':
                timerProGenArgs->period=atoi(optarg);
                break;
            case 's':
                timerScheArgs->period=atoi(optarg);
                break;
            case 'q':
                free(fcfs);
                fcfs = init_queue(atoi(optarg));
                break;
            case 'c':
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

    init_machine(machine, number_of_cpus, number_of_cores, number_of_threads);
    print_machine(machine);
    scheArgs->fcfs = fcfs;
    scheArgs->machine = machine;
    printf("\tAukeratutako argumentuak:\n\
            p: process generator-en periodoa: %d\n\
            s: schedule-aren periodoa: %d\n\
            q: process queue-aren periodo: %d\n",timerProGenArgs->period,timerScheArgs->period, fcfs->size);

    sleep (3);

    for(int i = 0; i < machine->number_of_cpus; i++){
        for(int j = 0; j < machine->cpus[i]->number_of_cores; j++){
            for(int k = 0; k < machine->cpus[i]->cores[j]->number_of_threads; k++){
                pthread_t threadId = i * j + k;
                threadArgs = malloc(sizeof(thread_args));
                threadArgs->machine = machine;
                threadArgs->cpu_id = i;
                threadArgs->core_id = j;
                threadArgs->thread_id = k;
                threadArgs->pcbList = pcbList;
                pthread_create(&threadId, NULL, &run_thread, threadArgs);
            }
        }
    }
    proGenArgs->pcbList=pcbList;
    proGenArgs->fcfs=fcfs;
    pthread_create(&proGenId, NULL, &process_generator, proGenArgs);
    pthread_create(&scheId, NULL, &schedule, scheArgs);
    pthread_create(&timerProGenId, NULL, &start_timer, timerProGenArgs);
    pthread_create(&timerScheId, NULL, &start_timer, timerScheArgs);
    pthread_create(&clockId, NULL, &start_clock, clockArgs);
    pthread_join(clockId, NULL);
    return 0;
}