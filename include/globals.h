#ifndef _GLOBALS_H
#define _GLOBALS_H
extern unsigned int _CLOCK;
extern pthread_mutex_t _CLOCK_MUTEX;
extern pthread_cond_t clock_cond;
#endif