#include "../include/fcfs.h"

process_queue * init_queue(int size){
    process_queue *fcfs = malloc(sizeof(process_queue));
    fcfs->size = size;
    fcfs->last_pos = 0;
    fcfs->queue = malloc(size*sizeof(pcb*));
    return fcfs;
}

void addInQueue(process_queue *fcfs, pcb* process){
    if(fcfs->last_pos>=fcfs->size){
        printf("FCFS queue is full\n");
    }
    else{
        fcfs->queue[fcfs->last_pos] = process;
        fcfs->last_pos++;
    }
}