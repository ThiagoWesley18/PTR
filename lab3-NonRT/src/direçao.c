#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitorRef.h"
#include "mainLib.h"
#include "direçao.h"
#include "utils.h"

// Transformada inversa de Laplace para Ymx e Ymy
double ymx_ref(double t) {
    return a1 * exp(-a1 * t);
}

double ymy_ref(double t) {
    return a2 * exp(-a2 * t);
}

void *dir(void *arg) {
    double t, Ymy, Ymx;
    thread_args_t *args = (thread_args_t*)arg;
    SharedMemoRef *shm = (SharedMemoRef*)args->ref;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        Ymy = ymy_ref(t);
        Ymx = ymx_ref(t);
         
        set_Ymx(shm, Ymx);
    
        set_Ymy(shm, Ymy);

        //printf("%f %f %f\n", t, Ymy);
        struct timespec req = {.tv_sec = 0, .tv_nsec = 50000000};
        nanosleep(&req, NULL);
    }
    return NULL;
}