#ifndef SIMULACAOLIB_H
#define SIMULACAOLIB_H
#include "../Matrix.h"

typedef struct array {
    double in[2];
}Array;

Matrix estado(Matrix B, Matrix u);
Matrix saida(Matrix C, Matrix x);
Array entrada(double t);
void resultado(double t, Matrix u, Matrix y);
void simula(Matrix B, Matrix C);

#endif