#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitor.h"
#include "uthread.h"
#include "utils.h"


double calc_v(double t) {
    if(t < 0.0){
        return 0.0;
    }else if (t >= 0.0 && t < 10.0){
        return 1.0;
    }else 
        return 1.0;
}

double calc_w(double t) {
    if(t < 0.0){
        return 0.0;
    }else if(t >= 0.0 && t < 10.0){
        return 0.2 * M_PI;
    }else 
        return -0.2 * M_PI;
}

void *uthread(void *arg) {
    double t, v, w, y1, y2, y3;
    SharedMemo *shm = (SharedMemo *)arg;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        v = calc_v(t);
        w = calc_w(t);

        setV(shm, v);
        setW(shm, w);

        y1 = getY1(shm);
        y2 = getY2(shm);
        y3 = getY3(shm);


        printf("%f,%f,%f,%f,%f,%f\n", t, v, w, y1, y2, y3);
        struct timespec req = {.tv_sec = 0, .tv_nsec = 30000000};
        nanosleep(&req, NULL);
    }
    return NULL;
}


//put code here
