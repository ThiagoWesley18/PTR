/*
	FILE: monitor.c
	DESCRIPTION: implementation of monitor
	AUTHOR: Andre Cavalcante
	DATE: august, 2024
	LICENSE: CC BY-SA
*/

#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "monitor.h"

void monitor_init(SharedMemo *shm) {
	*shm = (SharedMemo){0};
}

void monitor_destroy(SharedMemo *shm) {
	*shm = (SharedMemo){0};
}


void setV(SharedMemo *shm, double v) {
    	shm->v = v;
}

double getV(SharedMemo *shm) {
	double v;
		v = shm->v;
    return v;
}

void setW(SharedMemo *shm, double w) {
    	shm->w = w;
}

double getW(SharedMemo *shm) {
	double w;
		w = shm->w;
    return w;
}

void setY1(SharedMemo *shm, double y1) {
    	shm->y1 = y1;
}

double getY1(SharedMemo *shm) {
	double y1;
		y1 = shm->y1;
    return y1;
}

void setY2(SharedMemo *shm, double y2) {
    	shm->y2 = y2;
}

double getY2(SharedMemo *shm) {
	double y2;
		y2 = shm->y2;
    return y2;
}

void setY3(SharedMemo *shm, double y3) {
    	shm->y3 = y3;
}

double getY3(SharedMemo *shm) {
	double y3;
		y3 = shm->y3;
    return y3;
}
