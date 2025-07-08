#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monitorSaida.h"
#include "mainLib.h"
#include "simulaçao.h"
#include "utils.h"


//Matrix X
static double xc = 0.0;
static double yc = 0.0;
static double theta = 0.0;

double calc_y1(double t, double v, double w) {
    // Integração numérica usando o método do trapézio
    static double integral_x = 0.0;  // Acumulador para a integral
    static double last_x = 0.0;      // Valor de x na iteração anterior
    static double last_t = 0.0;      // Valor de t na iteração anterior

    (void)w;
    
    // Cálculo do valor atual (derivada)
    double x_dot = v * cos(theta);
    
    if (t > last_t) {
        integral_x += 0.5 * (x_dot + last_x) * (t - last_t);
    }
    
    last_x = x_dot;
    last_t = t;
    
    xc = integral_x;  // Atualiza a variável global
    return xc + R * cos(theta);
}

double calc_y2(double t, double v, double w) {
    // Integração numérica usando o método do trapézio
    static double integral_y = 0.0;  // Acumulador para a integral
    static double last_y = 0.0;      // Valor de y na iteração anterior
    static double last_t = 0.0;      // Valor de t na iteração anterior
    
    (void)w;
    
    // Cálculo do valor atual (derivada)
    double y_dot = v * sin(theta);
    
    if (t > last_t) {
        integral_y += 0.5 * (y_dot + last_y) * (t - last_t);
    }
    
    last_y = y_dot;
    last_t = t;
    
    yc = integral_y;  // Atualiza a variável global
    return yc + R * sin(theta);
}

void calc_x3(double t, double v, double w) {
    // Integração numérica usando o método do trapézio
    static double integral_theta = 0.0;  // Acumulador para a integral
    static double last_w = 0.0;          // Valor de w na iteração anterior
    static double last_t = 0.0;          // Valor de t na iteração anterior
    
    (void)v;
    
    if (t > last_t) {
        integral_theta += 0.5 * (w + last_w) * (t - last_t);
    }
    
    last_w = w;
    last_t = t;
    
    theta = integral_theta;  // Atualiza a variável global
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