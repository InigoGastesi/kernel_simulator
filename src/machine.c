#include "../include/machine.h"

void init_machine(machine *machine, int number_of_cpus, int number_of_cores, int number_of_threads){
    machine->number_of_cpus = number_of_cpus;
    machine->cpus = malloc(number_of_cpus*sizeof(cpu*));
    for(int i = 0; i < number_of_cpus; i++){
        machine->cpus[i] = malloc(sizeof(cpu));
        machine->cpus[i]->id = i;
        machine->cpus[i]->number_of_cores = number_of_cores;
        machine->cpus[i]->cores = malloc(number_of_cores*sizeof(core*));
        for(int j = 0; j < number_of_cores; j++){
            machine->cpus[i]->cores[j] = malloc(sizeof(core));
            machine->cpus[i]->cores[j]->id = j;
            machine->cpus[i]->cores[j]->number_of_threads = number_of_threads;
            machine->cpus[i]->cores[j]->threads = malloc(number_of_threads*sizeof(thread*));
            for(int k = 0; k < number_of_threads; k++){
                machine->cpus[i]->cores[j]->threads[k] = malloc(sizeof(thread));
                machine->cpus[i]->cores[j]->threads[k]->id=k;
            }
        }
    }
}

void print_machine(machine *machine){
    for(int i = 0; i < machine->number_of_cpus; i++){
        machine->cpus[i]->id = i;
        printf("####cpu number: %d####\n",machine->cpus[i]->id);
        for(int j = 0; j < machine->cpus[i]->number_of_cores; j++){
            printf("@@@@core number: %d@@@@\n",machine->cpus[i]->cores[j]->id);
            for(int k = 0; k < machine->cpus[i]->cores[j]->number_of_threads; k++){
                printf("number of thread: %d\n", machine->cpus[i]->cores[j]->threads[k]->id);
            }
            printf("@@@@@@@@@@@@@@@@@@@@@@@\n");
        }
        printf("#######################\n");
    }
}

void *run_thread(void *args){
    thread_args *arguments = (thread_args*) args;
    unsigned int thread_id = arguments->thread_id;
    unsigned int core_id = arguments->core_id;
    unsigned int cpu_id = arguments->cpu_id;
    machine *machine = arguments->machine;
    pcb_list *pcbList = arguments->pcbList;
    sem_t *sem = arguments->sem;
    while(1){
        sem_wait(sem);
        if(machine->cpus[cpu_id]->cores[core_id]->threads[thread_id]->process == NULL){
            continue;
        }
        else{
            printf("running process:%d, cpu: %d, core: %d, thread:%d\n", machine->cpus[cpu_id]->cores[core_id]->threads[thread_id]->process->pid, machine->cpus[cpu_id]->id, machine->cpus[cpu_id]->cores[core_id]->id, machine->cpus[cpu_id]->cores[core_id]->threads[thread_id]->id);
            sleep(1);
            printf("process end\n");
            delete_pcb(machine->cpus[cpu_id]->cores[core_id]->threads[thread_id]->process, pcbList);
            machine->cpus[cpu_id]->cores[core_id]->threads[thread_id]->process = NULL;
        }
    }
}
