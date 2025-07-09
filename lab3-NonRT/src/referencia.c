#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitorRef.h"
#include "mainLib.h"
#include "referencia.h"
#include "utils.h"


double x_ref(double t) {
    return (5 / M_PI) * cos(0.2 * M_PI * t);
}

double y_ref(double t) {

    if((t >= 0.0 ) && (t < 10.0)){
        return (5 / M_PI) * sin(0.2 * M_PI * t);
    }
    else {
        return (-5 / M_PI) * sin(0.2 * M_PI * t);
    }
}

void *uthread(void *arg) {
    double t, xref, yref;
    thread_args_t *args = (thread_args_t*)arg;
    SharedMemoRef *shm = (SharedMemoRef*)args->ref;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        xref = x_ref(t);
        yref = y_ref(t);

        set_xref(shm, xref);
        set_yref(shm, yref);

        //printf("%f %f %f\n", t, xref, yref);
        struct timespec req = {.tv_sec = 0, .tv_nsec = 120000000};
        nanosleep(&req, NULL);
    }
    return NULL;
}