#include "../include/clock.h"
#include "../include/timer.h"
#include <pthread.h>


int main(int argc, char *argv[]){
    int freq = 100000;
    if (argc ==2){
        freq = atoi(argv[1]);
    }

    pthread_t timerId, clockId;
    pthread_create(&timerId, NULL, &start_timer, NULL);
    pthread_create(&clockId, NULL, &start_clock, (void*)freq);
    pthread_join(clockId, NULL);
    return 0;
}