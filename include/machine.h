#ifndef _MACHINE_H
#define _MACHINE_H
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "globals.h"
void init_machine(machine *machine, int number_of_cpus, int number_of_cores, int number_of_threads);
void print_machine(machine *machine);
void *run_thread(void *args);
#endif 