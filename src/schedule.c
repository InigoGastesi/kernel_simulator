#include "../include/schedule.h"

/**
 * @brief schedulera martxan jartzen du. Momentuz ez du ezer egiten.
 * Bakarrik timeraren seinale itxaron eta mezu bat printeatu.
 * @param
 * @return
 */
void *schedule(void *args){
    while(1){
        sem_wait(&_SCHE_SEM);
        printf("###########################################################\n");
        printf("schedule running\n");
    }
}