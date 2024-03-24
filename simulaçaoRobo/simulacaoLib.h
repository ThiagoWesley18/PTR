#ifndef SIMULACAOLIB_H
#define SIMULACAOLIB_H
#include "../LIB_ADT/Matrix.h"
#include <pthread.h>

typedef struct array {
    double in[2];
}Array;

Matrix calcula_proximo_estado(Matrix matriz_estado_B, Matrix u);
Matrix calcula_sinal_de_saida(Matrix matriz_estado_C, Matrix matriz_estado_X);
Array calcula_sinal_de_entrada(double t);
void  integral_matriz_X(Matrix matriz_estado_X);
void espera_thread(int milisegundos);
void imprimi_resultado(double t, Matrix u, Matrix y);
void atualiza_matriz_B(Matrix matriz_estado_B, Matrix matriz_estado_X);
void* thread_Produtora();
void* thread_Consumidora();
void* thread_Saida();

#endif