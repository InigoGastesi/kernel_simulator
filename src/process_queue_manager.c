#include "../include/process_queue_manager.h"
#include <pthread.h>

void *process_generator(void * args){
    pro_gen_args *arguments = (pro_gen_args * )args;
    unsigned int counter = 0;
    unsigned int period = arguments->period;
    process_queue *processQueue = arguments->processQueue;
    

    while(1){
        
        while(counter < period){
            pthread_cond_wait(&_PRO_GEN_MUTEX_COND, &_PRO_GEN_MUTEX);
            counter++;
            printf("process gen counter:%d\n", counter);
        }
        counter = 0;
        add_pcb(processQueue);
        print_processQueue(processQueue);
        
    }
}

void add_pcb(process_queue *processQueue){
    pcb *new_process;
    new_process = malloc(sizeof(pcb));
    if (processQueue->first == NULL){
        new_process->pid=_PID;
        processQueue->first=new_process;
        processQueue->last=new_process;
    }
    else{
        _PID++;
        new_process->pid = _PID;
        new_process->prev = processQueue->last;
        processQueue->last->next=new_process;
        processQueue->last=new_process;
    }
}

void print_processQueue(process_queue *processQueue){
    pcb *process = processQueue->first;
    while (process != NULL){
        printf("Process pid:%d\n", process->pid);
        process=process->next;
    }
}