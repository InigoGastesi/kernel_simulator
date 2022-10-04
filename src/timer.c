#include "../include/timer.h"

unsigned int _CLOCK;
void* start_timer(void * args){
    unsigned int frequency = 1000000;
    while (1){    
        if(_CLOCK < frequency){
            _CLOCK++;
        }
        _CLOCK = 0;
        printf("%d\n",_CLOCK);
    }

}