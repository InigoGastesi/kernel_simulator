#include "../include/pcb_list_manager.h"

/**
 * @brief process generatora hasieratzen da. Timeraren seinalera itxaroten gelditzen da.
 * Seinalea jasotzerakoan, prozesu bat sortu eta pcb_lista printeatzen du. Hau denbora osoan egiten du.
 * @param pro_gen_args pcb_listaren pointer-a
 * @return
 */
void *process_generator(void * args){
    pro_gen_args *arguments = (pro_gen_args *)args;
    unsigned int counter = 0;
    pcb_list *pcbList = arguments->pcbList;
    process_queue *fcfs = arguments->fcfs;
    while(1){
        sem_wait(&_PRO_GEN_SEM);        
        add_pcb(pcbList, fcfs);
        print_pcbList(pcbList);
    }
}

/**
 * @brief pcb berri bat sortu, pcb_listan eta process_queuean ere sartzen da. 
 * @param pcb_list pcb_listaren pointer-a
 * @return
 */
void add_pcb(pcb_list *pcbList, process_queue *fcfs){
    if(fcfs->last_pos+1>=fcfs->size){
        return;
    }
    pcb *new_process = malloc(sizeof(pcb));
    if (pcbList->first == NULL){
        new_process->pid=_PID;
        pcbList->first=new_process;
        pcbList->last=new_process;
    }
    else{
        _PID++;
        new_process->pid = _PID;
        new_process->prev = pcbList->last;
        pcbList->last->next=new_process;
        pcbList->last=new_process;
    }
    push_queue(fcfs, new_process);

}

/**
 * @brief pcbListatik processu bat kentzen du. 
 * @param pcb_list pcb_listaren pointer-a
 * @param process kenduko den prozesuaren pointer-a
 * @return
 */
void delete_pcb(pcb *process, pcb_list *pcbList){
    if(pcbList->first->pid == process->pid){
        pcbList->first = pcbList->first->next;
    }
    if(pcbList->last->pid == process->pid){
        pcbList->last = pcbList->last->prev;
    }
    if(process->next == NULL){
        process->prev->next = process->next;
    }
    else if(process->prev == NULL)
    {
        process->next->prev = process->prev;
    }
    else{
        process->next->prev = process->prev;
        process->prev->next = process->next;
    }
    printf("delete pcb\n");
    free(process);
}

/**
 * @brief pcb_list osoa printeatzen du.
 * @param pcb_list pcb_listaren pointer-a
 * @return
 */
void print_pcbList(pcb_list *pcbList){
    pcb *process = pcbList->first;
    printf("-----------------------------------------------------------\n");
    printf("process listaren edukiak\n");
    while (process != NULL){
        printf("Process pid:%d\n", process->pid);
        process=process->next;
    }
}