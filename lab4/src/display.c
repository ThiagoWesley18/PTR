#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"
#include "monitorRef.h"
#include "monitorSaida.h"
#include "mainLib.h"
#include "utils.h"


void *display_print(void *arg) {
    thread_args_t *args = (thread_args_t*)arg;
    SharedMemoRef *shmRef = (SharedMemoRef*)args->ref;
    SharedMemoSaida *shm = (SharedMemoSaida*)args->saida;
    BufferCompartilhado *buffer = (BufferCompartilhado*)args->buffer; // <- agora só um

    struct timespec tp_start, tp_stop;
    double y1, y2, teta, xref, yref;
    double t = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while (t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

        y1 = get_y1(shm);
        y2 = get_y2(shm);
        teta = get_x3(shm);
        xref = get_xref(shmRef);
        yref = get_yref(shmRef);

        // Atualiza SEMPRE sobrescrevendo
        snprintf(buffer->linha, MAX_STR_SIZE,
                 "%f,%f,%f,%f,%f,%f\n",
                 t, y1, y2, teta, xref, yref);

        struct timespec req = {.tv_sec = 0, .tv_nsec = 600000000};
        nanosleep(&req, NULL);
    }
    // Atualiza SEMPRE sobrescrevendo
    snprintf(buffer->linha, MAX_STR_SIZE, "-1");
    return NULL;
}


// void *display_print(void *arg) {
//     thread_args_t *args = (thread_args_t*)arg;
//     SharedMemoRef *shmRef = (SharedMemoRef*)args->ref;
//     SharedMemoSaida *shm = (SharedMemoSaida*)args->saida;
//     struct timespec tp_start, tp_stop;
//     double y1, y2, teta, xref, yref;
//     double t = 0.0;

//     clock_gettime(CLOCK_MONOTONIC, &tp_start);
//     while(t < 20.0 ) {
//         clock_gettime(CLOCK_MONOTONIC, &tp_stop);
//         t = timespec_diff(&tp_start, &tp_stop);

//         y1 = get_y1(shm);
//         y2 = get_y2(shm);
//         teta = get_x3(shm);
//         xref = get_xref(shmRef);
//         yref = get_yref(shmRef);

//         printf("%f,%f,%f,%f,%f,%f\n", t, y1, y2, teta, xref, yref);

//         struct timespec req = {.tv_sec = 0, .tv_nsec = 600000000};
//         nanosleep(&req, NULL);
//     }
//     return NULL;
// }