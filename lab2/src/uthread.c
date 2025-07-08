/*
	FILE: uthread.c
	DESCRIPTION: implementation of module
	AUTHOR: Andre Cavalcante
	DATE: august, 2024
	LICENSE: CC BY-SA
*/

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitor.h"
#include "uthread.h"
#include "utils.h"


double calc_v(double t) {
    if(t < 0.0) 
        return 0.0;
    else if (t >= 0.0 && t < 10.0)
        return 1.0;
    else if (t >= 10.0 && t < 20.0)
        return 1.0;
    else
        return 0.0;
}

double calc_w(double t) {
    if(t < 0.0)
        return 0.0;
    else if(t >= 0.0 && t < 10.0)
        return 0.2 * 3.141592;
    else if (t >= 10.0 && t < 20.0)
        return -0.2 * 3.141592;
    else
        return 0.0;
}

void u(SharedMemo *shm, double t) {
    double  v, w, y1, y2, y3;
   
    v = calc_v(t);
    w = calc_w(t);

    setV(shm, v);
    setW(shm, w);

    y1 = getY1(shm);
    y2 = getY2(shm);
    y3 = getY3(shm);

    printf("%f,%f,%f,%f,%f,%f\n", t, v, w, y1, y2, y3);
}


//put code here
