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
#include "display.h"

//int main(int argc, char *argv[])
int main()
{
	printf("t,v,w,y1,y2,y3\n");

	pthread_t uthr;
	pthread_t ythr;
	pthread_t display_thr;

	SharedMemo shared, *shm = &shared;
	
	monitor_init(shm);

	pthread_create(&uthr, NULL, uthread, shm);
	pthread_create(&ythr, NULL, yfthread, shm);
	pthread_create(&display_thr, NULL, display_print, shm);
	
	pthread_join(ythr, NULL);
	pthread_join(uthr, NULL);
	pthread_join(display_thr, NULL);
	
	monitor_destroy(shm);


	return EXIT_SUCCESS;
}
