#ifndef SIMULACAOLIB_H
#define SIMULACAOLIB_H
#include "../LIB_ADT/Matrix.h"
#include <pthread.h>

typedef struct array {
    double in[2];
}Array;

typedef struct{
    double t;
    Matrix B;
    Matrix u;
    Matrix Estado;
}args_th1;

typedef struct{
    Matrix C;
    Matrix Estado;
    double t;
    Matrix u;
    Matrix y;
}args_th2;

extern pthread_mutex_t lock; // Define the "lock" identifier

Matrix estado(Matrix B, Matrix u);
Matrix saida(Matrix C, Matrix x);
Array entrada(double t);
void resultado(double t, Matrix u, Matrix y);
Matrix simula(Matrix B, Matrix u, Array v);
void* thread_1(void* agr);
void* thread_2(void* agr);

#endif