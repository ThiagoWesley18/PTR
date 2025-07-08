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


const double DELTA = (20.0/0.05);

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

	return xc;
}

double calc_y2(double t, double v, double w) {
	static double ycdot_prev = 0.0;

	(void)t;
	(void)v;

	double ycdot = w * cos(teta);
	yc =  (ycdot + ycdot_prev) * DELTA / 2;
	ycdot_prev = ycdot;

	return yc;
}

double calc_y3(double t, double v, double w) {
	static double tetadot_prev = 0.0;

	(void)t;
	(void)v;

	double tetadot = w;
	teta = (tetadot + tetadot_prev) * DELTA / 2;
	tetadot_prev = tetadot;

	return teta;
}

void y(SharedMemo *shm, double t) {
	double v, w, y1, y2, y3;
    

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

	
}


