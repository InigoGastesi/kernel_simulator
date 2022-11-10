#include "../include/schedule.h"

void *schedule(void *args){
    while(1){
        sem_wait(&_SCHE_SEM);
        printf("###########################################################\n");
        printf("schedule running\n");
    }
}