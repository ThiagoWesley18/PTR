#ifndef SIMULACAOLIB_H
#define SIMULACAOLIB_H
#include "../LIB_ADT/Matrix.h"
#include <pthread.h>

typedef struct array {
    double in[2];
}Array;



Matrix estado(Matrix B, Matrix u);
Matrix saida(Matrix C, Matrix x);
Array entrada(double t);
void resultado(double t, Matrix u, Matrix y);
void atualizaB(Matrix B, Matrix x);
void* thread_1(void* agr);
void* thread_2(void* agr);

#endif