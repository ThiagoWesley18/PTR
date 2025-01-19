#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "controle.h"
#include "monitorRef.h"
#include "monitorSaida.h"
#include "mainLib.h"
#include "utils.h"

void *controle(void *arg) {
    double t, vx, vy, DYmx, DYmy, Ymx, Ymy, y1, y2, xref, yref;
    thread_args_t *args = (thread_args_t*)arg;
    SharedMemoRef *shmRef = (SharedMemoRef*)args->ref;
    SharedMemoSaida *shm = (SharedMemoSaida*)args->saida;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        y1 = get_y1(shm);
        y2 = get_y2(shm);

        Ymx = get_Ymx(shmRef);
        Ymy = get_Ymy(shmRef);

        xref = get_xref(shmRef);
        yref = get_yref(shmRef);

        DYmx = a1 * (xref - Ymx);
        DYmy = a2 * (yref - Ymy);

        vx =  DYmx + a1 * (Ymx - y1);
        vy =  DYmy + a2 * (Ymy - y2);

        set_vx(shm, vx);
        set_vy(shm, vy);

         
        //printf("%f %f %f\n", t, y1, y2);
        struct timespec req = {.tv_sec = 0, .tv_nsec = 50000000};
        nanosleep(&req, NULL);
    }
    return NULL;
}

