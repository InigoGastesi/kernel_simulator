#include "../include/clock.h"
#include "../include/timer.h"
#include <pthread.h>

int main(int argc, char *argv[]){
    int freq = atoi(argv[1]);
    pthread_t timerId, clockId;
    pthread_create(&timerId, NULL, &start_timer, (void*)freq);
    pthread_create(&clockId, NULL, &start_clock, NULL);
    pthread_join(timerId, NULL);
    return 0;
}