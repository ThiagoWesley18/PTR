#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "monitor.h"
#include "uthread.h"
#include "yfthread.h"

int main()
{
	printf("t,v,w,y1,y2,y3\n");

	pthread_t uthr;
	pthread_t ythr;

	SharedMemo shared, *shm = &shared;
	
	monitor_init(shm);

	pthread_create(&uthr, NULL, uthread, shm);
	pthread_create(&ythr, NULL, yfthread, shm);
	
	pthread_join(ythr, NULL);
	pthread_join(uthr, NULL);
	
	monitor_destroy(shm);


	return EXIT_SUCCESS;
}
