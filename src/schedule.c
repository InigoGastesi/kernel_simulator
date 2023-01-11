#include "../include/schedule.h"

/**
 * @brief schedulera martxan jartzen du. 
 * @param args sche_args estrukturatik argumentuak jasotzen ditu
 * @param machine machine estruktura
 * @param processQueue process queuea
 * @return
 */
void *schedule(void *args){
    sche_args *arguments = (sche_args*)args;
    machine *machine = arguments->machine;
    process_queue *processQueue = arguments->processQueue;
    pcb *process;
    while(1){
        sem_wait(&_SCHE_SEM);
        //printf("###########################################################\n");
        //printf("schedule running\n");
        for(int i = 0; i < machine->number_of_cpus; i++){
            for(int j = 0; j < machine->cpus[i]->number_of_cores; j++){
                for(int k = 0; k < machine->cpus[i]->cores[j]->number_of_threads; k++){
                    if(machine->cpus[i]->cores[j]->threads[k]->process == NULL){
                        process = pop_queue(processQueue);
                        process->state = 1;
                        machine->cpus[i]->cores[j]->threads[k]->process = process;
                    }
                }
            }
        }
    }
}