#include "../include/clock.h"
#include "../include/timer.h"
#include <pthread.h>

int main(int argc, char *argv[]){
    int freq = atoi(argv[1]);
    pthread_t id;
    pthread_create(&id, NULL, start_timer, NULL);
    return 0;
}