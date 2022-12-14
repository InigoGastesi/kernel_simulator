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
    
    while(1){
        sem_wait(&_PRO_GEN_SEM);        
        add_pcb(pcbList);
        print_pcbList(pcbList);
    }
}

/**
 * @brief pcb berri bat sortu eta pcb_listan  sartzen du. 
 * @param pcb_list pcb_listaren pointer-a
 * @return
 */
void add_pcb(pcb_list *pcbList){
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