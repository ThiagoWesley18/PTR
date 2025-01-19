/*
	FILE: main.c
	DESCR: entry point of the program
	AUTHOR: Andre Cavalcante
	DATE: august, 2024
	LICENSE: CC BY-SA
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "monitor.h"
#include "uthread.h"
#include "yfthread.h"
#include "utils.h"

//int main(int argc, char *argv[])
int main()
{
	SharedMemo shm;
    double t = 0.0;
    struct timespec tp_start, tp_stop;
	
	printf("t,v,w,y1,y2,y3\n");
	monitor_init(&shm);
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);


        u(&shm, t);
        y(&shm, t);
    }
	
	monitor_destroy(&shm);
	return EXIT_SUCCESS;
}