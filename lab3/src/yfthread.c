/*
	FILE: yfthead.c
	DESCRIPTION: implementation of module
	AUTHOR: Andre Cavalcante
	DATE: august, 2024
	LICENSE: CC BY-SA
*/

#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "monitor.h"
#include "utils.h"
#include "yfthread.h"

const double D= 0.30;
const double DELTA = (20.0/0.030);

//Matrix X
static double xc = 0.0;
static double yc = 0.0;
static double teta = 0.0;

double calc_y1(double t, double v, double w) {
	static double xcdot_prev = 0.0;

	(void)t;
	(void)w;

	double xcdot = v * sin(teta);
	xc =  (xcdot + xcdot_prev) * DELTA / 2;
	xcdot_prev = xcdot;

	return xc + 0.5 * D * cos(teta) * xc;
}

double calc_y2(double t, double v, double w) {
	static double ycdot_prev = 0.0;

	(void)t;
	(void)v;

	double ycdot = w * cos(teta);
	yc =  (ycdot + ycdot_prev) * DELTA / 2;
	ycdot_prev = ycdot;

	return yc + 0.5 * D * sin(teta) * yc;
}

double calc_y3(double t, double v, double w) {
	static double tetadot_prev = 0.0;

	(void)t;
	(void)v;

	double tetadot = w;
	teta = (tetadot + tetadot_prev) * DELTA / 2;
	tetadot_prev = tetadot;

	return 2 * teta;
}

void *yfthread(void *arg) {
	double t, v, w, y1, y2, y3;
    SharedMemo *shm = (SharedMemo *)arg;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {	//t in seconds
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

		//getU
		v = getV(shm);
		w = getW(shm);

		//calc Y
		y1 = calc_y1(t, v, w);
		y2 = calc_y2(t, v, w);
		y3 = calc_y3(t, v, w);

		//setY
		setY1(shm, y1);
		setY2(shm, y2);
		setY3(shm, y3);

        struct timespec req = {.tv_sec = 0, .tv_nsec = 50000000};
        nanosleep(&req, NULL);
	}

	return NULL;
}


