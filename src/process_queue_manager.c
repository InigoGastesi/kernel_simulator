#include "../include/process_queue_manager.h"


/**
 * @brief Process_queuea hasieratzen du
 * @param size process_queuearen tamaina
 * @return process_queuea hasieratua itzultzen du.
 */
process_queue * init_queue(int size){
    process_queue *processQueue = malloc(sizeof(process_queue));
    processQueue->size = size;
    processQueue->last_pos = -1;
    processQueue->queue = malloc(size*sizeof(pcb*));
    return processQueue;
}

/**
 * @brief Process_queuean prozesu bat sartzen du azkeneko posizioan
 * @param processQueue process_queuea.
 * @param process prozesu berria.
 * @return
 */
void push_queue(process_queue *processQueue, pcb* process){
    pthread_mutex_lock(&_QUEUE);
    if(processQueue->last_pos+1>=processQueue->size){
        //printf("processQueue queue is full\n");
    }
    else{
        processQueue->queue[processQueue->last_pos+1] = process;
        processQueue->last_pos++;
    }
    pthread_mutex_unlock(&_QUEUE);
}

void print_queue(process_queue *processQueue){
    printf("#############################\n");
    for (int i = 0; i <= processQueue->last_pos; i++){
        printf("process pid queue: %d\n", processQueue->queue[i]->pid);
    }
}

/**
 * @brief Process_queuearen lehenengo elementua itzuli eta queueatik kentzen du
 * @param processQueue process_queuea.
 * @return queuaren lehenengo elementua.
 */
pcb *pop_queue(process_queue *processQueue){
    pthread_mutex_lock(&_QUEUE);
    pcb *process = NULL;
    if(processQueue->last_pos != -1){
        process = processQueue->queue[0];
    
        for (int i=0; i < processQueue->last_pos; i++){
            processQueue->queue[i] = processQueue->queue[i+1];
        }
        processQueue->last_pos--;
        
    }
    pthread_mutex_unlock(&_QUEUE);

    return process;
}