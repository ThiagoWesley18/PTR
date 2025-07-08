#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitorSaida.h"
#include "mainLib.h"
#include "Matrix.h"
#include "linearizaçao.h"
#include "utils.h"

void *linearizaçao(void *arg) {
    double t, x3, u1, u2, vx, vy;
    Matrix L = newMatrix(2, 2);
    Matrix v = newMatrix(2, 1);
    Matrix L_inv = newMatrix(2, 2);
    Matrix u = newMatrix(2, 1);

    thread_args_t *args = (thread_args_t*)arg;
    SharedMemoSaida *shm = (SharedMemoSaida*)args->saida;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        vx = get_vx(shm);
        vy = get_vy(shm);
        x3 = get_x3(shm);

        v.matriz[0][0] = vx;
        v.matriz[1][0] = vy;

        L.matriz[0][0] = cos(x3);
        L.matriz[0][1] = -R * sin(x3);
        L.matriz[1][0] = sin(x3);
        L.matriz[1][1] = R * cos(x3);

        L_inv = inversaMatrix(L);
        u = multMatrix(L_inv, v);

        u1 = u.matriz[0][0];
        u2 = u.matriz[1][0];

        set_u1(shm, u1);
        set_u2(shm, u2);

        //printf("%f %f %f\n", t, vx, vy);
        struct timespec req = {.tv_sec = 0, .tv_nsec = 40000000};
        nanosleep(&req, NULL);
    }

    freeMatrix(&L, &v, &L_inv, &u, NULL);

    return NULL;
}