#include "../include/fcfs.h"


/**
 * @brief Process_queuea hasieratzen du
 * @param size process_queuearen tamaina
 * @return process_queuea hasieratua itzultzen du.
 */
process_queue * init_queue(int size){
    process_queue *fcfs = malloc(sizeof(process_queue));
    fcfs->size = size;
    fcfs->last_pos = -1;
    fcfs->queue = malloc(size*sizeof(pcb*));
    return fcfs;
}

/**
 * @brief Process_queuean prozesu bat sartzen du azkeneko posizioan
 * @param fcfs process_queuea.
 * @param process prozesu berria.
 * @return
 */
void push_queue(process_queue *fcfs, pcb* process){
    if(fcfs->last_pos+1>=fcfs->size){
        printf("FCFS queue is full\n");
    }
    else{
        fcfs->queue[fcfs->last_pos+1] = process;
        fcfs->last_pos++;
    }
}

/**
 * @brief Process_queuearen lehenengo elementua itzuli eta queueatik kentzen du
 * @param fcfs process_queuea.
 * @return queuaren lehenengo elementua.
 */
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