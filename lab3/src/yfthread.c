
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "monitor.h"
#include "utils.h"
#include "yfthread.h"

const double D = 0.30;

//Matrix X
static double teta = 0.0;

double calc_y1(double t, double v, double w) {
    //(void)t;
    (void)w;

    double xc = v * sin(teta);

    // Integração numérica de xc usando o método do trapézio
    static double integral_xc = 0.0; // Acumulador para a integral
    static double last_xc = 0.0;     // Valor de xc na iteração anterior
    static double last_t = 0.0;      // Valor de t na iteração anterior

    if (t > 0.0) {
        integral_xc += 0.5 * (xc + last_xc) * (t - last_t);
    }

    last_xc = xc;
    last_t = t;

    return integral_xc + 0.5 * D * cos(teta) * xc;
}

double calc_y2(double t, double v, double w) {
    //(void)t;
    (void)v;

    double yc = w * cos(teta);

    // Integração numérica de yc usando o método do trapézio
    static double integral_yc = 0.0; // Acumulador para a integral
    static double last_yc = 0.0;     // Valor de yc na iteração anterior
    static double last_t = 0.0;      // Valor de t na iteração anterior

    if (t > 0.0) {
        integral_yc += 0.5 * (yc + last_yc) * (t - last_t);
    }

    last_yc = yc;
    last_t = t;

    return integral_yc + 0.5 * D * sin(teta) * yc;
}

double calc_y3(double t, double v, double w) {
    (void)v;

    // Integração numérica de teta usando o método do trapézio
    static double integral_teta = 0.0; // Acumulador para a integral
    static double last_teta = 0.0;     // Valor de teta na iteração anterior
    static double last_t = 0.0;        // Valor de t na iteração anterior

    if (t > 0.0) {
        integral_teta += 0.5 * (w + last_teta) * (t - last_t);
    }

    last_teta = w;
    last_t = t;

	teta = integral_teta;
    return integral_teta;
}

void *yfthread(void *arg) {
	double t, v, w, y1, y2, y3;
    SharedMemo *shm = (SharedMemo *)arg;
    struct timespec tp_start, tp_stop;

    t = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &tp_start);
    while(t < 20.0) {	//t in seconds
        clock_gettime(CLOCK_MONOTONIC, &tp_stop);
        t = timespec_diff(&tp_start, &tp_stop);

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

        struct timespec req = {.tv_sec = 0, .tv_nsec = 50000000};
        nanosleep(&req, NULL);
	}

	return NULL;
}


