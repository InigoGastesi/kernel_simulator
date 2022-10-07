#include "../include/process_generator.h"
#include <pthread.h>

void *process_generator(void * args){
    pro_gen_args *arguments = args;
    unsigned int counter = 0;
    unsigned int period = arguments->period;
    pcb *process_control = arguments->procces_control;
    pthread_mutex_lock(&_PRO_GEN_MUTEX);
    while(counter < period){
        counter++;
    }
    counter = 0;
    process *new_process;
    if (process_control->first == NULL){
        new_process = malloc(sizeof(process));
        new_process->pid=0;
        process_control->first=new_process;
        process_control->last=new_process;
    }
    pthread_mutex_unlock(&_PRO_GEN_MUTEX);
}