/*
	FILE: monitor.h
	DESCRIPTION: public definitions of monitor
	AUTHOR: Andre Cavalcante
	DATE: August, 2024
	LICENSE: CC BY-SA
*/

#ifndef MONITOR_H__
#define MONITOR_H__

#include <pthread.h>

typedef struct { 
    double v;
    double w;
    double y1;
    double y2;
    double y3;
    pthread_mutex_t mutex;
} SharedMemo;

void monitor_init(SharedMemo *shm);
void monitor_destroy(SharedMemo *shm);

void setV(SharedMemo *shm, double v);
double getV(SharedMemo *shm);

void setW(SharedMemo *shm, double w);
double getW(SharedMemo *shm);

void setY1(SharedMemo *shm, double y1);
double getY1(SharedMemo *shm);

void setY2(SharedMemo *shm, double y2);
double getY2(SharedMemo *shm);

void setY3(SharedMemo *shm, double y3);
double getY3(SharedMemo *shm);


#endif //MONITOR_H__