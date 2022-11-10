#include "../include/pcb_list_manager.h"

void *process_generator(void * args){
    pro_gen_args *arguments = (pro_gen_args * )args;
    unsigned int counter = 0;
    pcb_list *processQueue = arguments->processQueue;
    

    while(1){
        sem_wait(&_PRO_GEN_SEM);        
        add_pcb(processQueue);
        print_processQueue(processQueue);
    }
}

void add_pcb(pcb_list *processQueue){
    pcb *new_process = malloc(sizeof(pcb));
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

void print_processQueue(pcb_list *processQueue){
    pcb *process = processQueue->first;
    printf("-----------------------------------------------------------\n");
    printf("process listaren edukiak\n");
    while (process != NULL){
        printf("Process pid:%d\n", process->pid);
        process=process->next;
    }
}