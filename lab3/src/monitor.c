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
    shm->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void monitor_destroy(SharedMemo *shm) {
    pthread_mutex_destroy(&(shm->mutex));
	*shm = (SharedMemo){0};
}


void setV(SharedMemo *shm, double v) {
	pthread_mutex_lock(&(shm->mutex));
    	shm->v = v;
	pthread_mutex_unlock(&(shm->mutex));
}

double getV(SharedMemo *shm) {
	double v;
	pthread_mutex_lock(&(shm->mutex));
		v = shm->v;
	pthread_mutex_unlock(&(shm->mutex));
    return v;
}

void setW(SharedMemo *shm, double w) {
	pthread_mutex_lock(&(shm->mutex));
    	shm->w = w;
	pthread_mutex_unlock(&(shm->mutex));
}

double getW(SharedMemo *shm) {
	double w;
	pthread_mutex_lock(&(shm->mutex));
		w = shm->w;
	pthread_mutex_unlock(&(shm->mutex));
    return w;
}

void setY1(SharedMemo *shm, double y1) {
	pthread_mutex_lock(&(shm->mutex));
    	shm->y1 = y1;
	pthread_mutex_unlock(&(shm->mutex));
}

double getY1(SharedMemo *shm) {
	double y1;
	pthread_mutex_lock(&(shm->mutex));
		y1 = shm->y1;
	pthread_mutex_unlock(&(shm->mutex));
    return y1;
}

void setY2(SharedMemo *shm, double y2) {
	pthread_mutex_lock(&(shm->mutex));
    	shm->y2 = y2;
	pthread_mutex_unlock(&(shm->mutex));
}

double getY2(SharedMemo *shm) {
	double y2;
	pthread_mutex_lock(&(shm->mutex));
		y2 = shm->y2;
	pthread_mutex_unlock(&(shm->mutex));
    return y2;
}

void setY3(SharedMemo *shm, double y3) {
	pthread_mutex_lock(&(shm->mutex));
    	shm->y3 = y3;
	pthread_mutex_unlock(&(shm->mutex));
}

double getY3(SharedMemo *shm) {
	double y3;
	pthread_mutex_lock(&(shm->mutex));
		y3 = shm->y3;
	pthread_mutex_unlock(&(shm->mutex));
    return y3;
}
