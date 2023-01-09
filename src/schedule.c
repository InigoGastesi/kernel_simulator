#include "../include/schedule.h"

/**
 * @brief schedulera martxan jartzen du. Momentuz ez du ezer egiten.
 * Bakarrik timeraren seinale itxaron eta mezu bat printeatu.
 * @param
 * @return
 */
void *schedule(void *args){
    sche_args *arguments = (sche_args*)args;
    machine *machine = arguments->machine;
    process_queue *fcfs = arguments->fcfs;
    while(1){
        sem_wait(&_SCHE_SEM);
        printf("###########################################################\n");
        printf("schedule running\n");
        for(int i = 0; i < machine->number_of_cpus; i++){
            for(int j = 0; j < machine->cpus[i]->number_of_cores; j++){
                for(int k = 0; k < machine->cpus[i]->cores[j]->number_of_threads; k++){
                    if(machine->cpus[i]->cores[j]->threads[k]->process == NULL){
                        machine->cpus[i]->cores[j]->threads[k]->process = pop_queue(fcfs);
                    }
                }
            }
        }
    }
}