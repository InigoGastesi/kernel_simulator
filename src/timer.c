#include "../include/timer.h"

unsigned int _CLOCK;
void* start_timer(void * args){

    unsigned int frequency = (int)args;
    while (1){
        if(_CLOCK < frequency){
            continue;
        }
        _CLOCK = 0;
        printf("%d\n",frequency);
    }

}