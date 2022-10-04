#include "../include/clock.h"
#include "../include/globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int _CLOCK;
void* start_clock(){
    _CLOCK = 0;
    while (1){
        _CLOCK++;
    }
}