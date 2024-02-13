#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulacaoLib.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Calcula o estado seguinte do robô
Matrix estado(Matrix B, Matrix u){
    return multMatrix(B, u);
}

// Calcula a saída do robô
Matrix saida(Matrix C, Matrix x){
    return multMatrix(C, x);
}

// Calcula a entrada do robô no instante de tempo t
Array entrada(double t){
    Array v;
    if(t < 10){
        v.in[0] = 1.0;
        v.in[1]= 0.2 * M_PI;
    }else if(t >= 10) {
        v.in[0] = 1.0;
        v.in[1] = -0.2 * M_PI;
    }
    return v;
}

// Imprime o resultado da simulação
void resultado(double t, Matrix u, Matrix y){
    printf("%lf    [%lf    %lf]    [%lf    %lf    %lf]\n", t, u.matriz[0][0], u.matriz[1][0], y.matriz[0][0], y.matriz[1][0], y.matriz[2][0]);
}