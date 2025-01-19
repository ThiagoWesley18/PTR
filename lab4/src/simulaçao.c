#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitorSaida.h"
#include "mainLib.h"
#include "simulaçao.h"
#include "utils.h"

const double DELTA = (20.0/0.030);

//Matrix X
static double xc = 0.0;
static double yc = 0.0;
static double theta = 0.0;

double calc_y1(double t, double v, double w) {
    static double xdot_prev = 0.0;

    (void)t;
    (void)w;

    double xdot = xc * cos(theta);
    xc =  (xdot + xdot_prev) * DELTA / 2;
    xdot_prev = xdot;

    return xc + R * cos(theta);
}

double calc_y2(double t, double v, double w) {
    static double ydot_prev = 0.0;

    (void)t;
    (void)v;

    double ydot = yc * sin(theta);
    yc =  (ydot + ydot_prev) * DELTA / 2;
    ydot_prev = ydot;

    return yc + R * sin(theta);
}

void calc_x3(double t, double v, double w) {
    static double thetadot_prev = 0.0;

    (void)t;
    (void)v;

    double thetadot = w;
    theta = (thetadot + thetadot_prev) * DELTA / 2;
    thetadot_prev = thetadot;

    //printf("%f %f %f\n", t, thetadot, theta);
}

void *robo(void *arg){
    double t, v, w, y1, y2;

    thread_args_t *args = (thread_args_t*)arg;
    SharedMemoSaida *shm = (SharedMemoSaida*)args->saida;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        v = get_u1(shm);
        w = get_u2(shm);

        y1 = calc_y1(t, v, w);
        y2 = calc_y2(t, v, w);
        calc_x3(t, v, w);

        set_y1(shm, y1);
        set_y2(shm, y2);
        set_x3(shm, theta);

        //printf("%f %f %f %f\n", t, y1, y2, x3);
        struct timespec req = {.tv_sec = 0, .tv_nsec = 30000000};
        nanosleep(&req, NULL);
    }
    return NULL;
}