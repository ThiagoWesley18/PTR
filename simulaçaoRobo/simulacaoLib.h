#ifndef SIMULACAOLIB_H
#define SIMULACAOLIB_H
#include "../LIB_ADT/Matrix.h"
#include "../LIB_ADT/Integral.h"

typedef struct array Array;
struct array {
    double in[2];
};



Matrix calcula_proximo_estado(Matrix matriz_estado_B, Matrix u);
Matrix calcula_sinal_de_saida(Matrix matriz_estado_C, Matrix matriz_estado_X , Matrix matriz_estado_D);
Array calcula_sinal_de_entrada(double t);
void integral_matriz_X(Matrix matriz_estado_X);
void espera_thread(int milisegundos);
void imprimi_resultado(double t, Matrix u, Matrix y);
void atualiza_matriz_B(Matrix matriz_estado_B, Matrix matriz_estado_X);
void atualiza_matriz_D(Matrix matriz_estado_D, Matrix matriz_estado_X, double D);
void* thread_Produtora(void* agr);
void* thread_Consumidora(void* agr);

#endif