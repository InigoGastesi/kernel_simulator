#include "../include/fcfs.h"

process_queue * init_queue(int size){
    process_queue *fcfs = malloc(sizeof(process_queue));
    fcfs->size = size;
    fcfs->last_pos = -1;
    fcfs->queue = malloc(size*sizeof(pcb*));
    return fcfs;
}

void push_queue(process_queue *fcfs, pcb* process){
    if(fcfs->last_pos+1>=fcfs->size){
        printf("FCFS queue is full\n");
    }
    else{
        fcfs->queue[fcfs->last_pos+1] = process;
        fcfs->last_pos++;
    }
}

pcb *pop_queue(process_queue *fcfs){
    pcb *process = NULL;
    if(fcfs->last_pos != -1){
        process = fcfs->queue[0];
    
        for (int i=0; i < fcfs->last_pos-1; i++){
            fcfs->queue[i] = fcfs->queue[i+1];
        }
        fcfs->last_pos--;
        
    }
    return process;
    
}