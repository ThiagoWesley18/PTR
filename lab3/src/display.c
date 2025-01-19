#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "display.h"
#include "monitor.h"
#include "utils.h"

void *display_print(void *arg) {
    SharedMemo *shm = (SharedMemo *)arg;
    struct timespec tp_start, tp_stop;
    double v, w, y1, y2, y3;
    double t = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);
        v = getV(shm);
        w = getW(shm);
        y1 = getY1(shm);
        y2 = getY2(shm);
        y3 = getY3(shm);

        printf("%f,%f,%f,%f,%f,%f\n", t, v, w, y1, y2, y3);
    }
    return NULL;
}