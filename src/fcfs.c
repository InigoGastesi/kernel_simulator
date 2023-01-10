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
    pthread_mutex_lock(&_QUEUE);
    if(fcfs->last_pos+1>=fcfs->size){
        printf("FCFS queue is full\n");
    }
    else{
        fcfs->queue[fcfs->last_pos+1] = process;
        fcfs->last_pos++;
    }
    pthread_mutex_unlock(&_QUEUE);
}

void print_queue(process_queue *fcfs){
    printf("#############################\n");
    for (int i = 0; i <= fcfs->last_pos; i++){
        printf("process pid queue: %d\n", fcfs->queue[i]->pid);
    }
}

/**
 * @brief Process_queuearen lehenengo elementua itzuli eta queueatik kentzen du
 * @param fcfs process_queuea.
 * @return queuaren lehenengo elementua.
 */
pcb *pop_queue(process_queue *fcfs){
    pthread_mutex_lock(&_QUEUE);
    pcb *process = NULL;
    if(fcfs->last_pos != -1){
        process = fcfs->queue[0];
    
        for (int i=0; i < fcfs->last_pos; i++){
            fcfs->queue[i] = fcfs->queue[i+1];
        }
        fcfs->last_pos--;
        
    }
    pthread_mutex_unlock(&_QUEUE);

    return process;

    
}