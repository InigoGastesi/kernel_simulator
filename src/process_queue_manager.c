#include "../include/process_queue_manager.h"

void *process_generator(void * args){
    pro_gen_args *arguments = args;
    unsigned int counter = 0;
    unsigned int period = arguments->period;
    process_queue *process_control = arguments->processQueue;
    pthread_mutex_lock(&_PRO_GEN_MUTEX);
    while(counter < period){
        counter++;
    }
    counter = 0;
    pcb *new_process;
    
    pthread_mutex_unlock(&_PRO_GEN_MUTEX);
}

void add_pcb(process_queue *processQueue){
    pcb *new_process;
    new_process = malloc(sizeof(pcb));
    if (processQueue->first == NULL){
        new_process->pid=0;
        processQueue->first=new_process;
        processQueue->last=new_process;
    }
    else{
        int pid = processQueue->last->pid + 1;
        new_process->pid = pid;
        new_process->prev = processQueue->last;
        processQueue->last=new_process;
    }
}