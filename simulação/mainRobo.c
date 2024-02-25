#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include "simulacaoLib.h"
#define intervalo 0.1
#define tempo 20.0
#define D 1.0

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Variaveis globais
Matrix matriz_estado_B;
Matrix matriz_estado_C;
Matrix matriz_estado_X;
Matrix matriz_entrada;

void* thread_Produtora(void*){
    for(double t = 0.0; t <= tempo; t+=intervalo){
        pthread_mutex_lock(&lock);
        Array v = calcula_sinal_de_entrada(t);

        matriz_entrada.matriz[0][0] = v.in[0];
        matriz_entrada.matriz[1][0] = v.in[1];
        pthread_mutex_unlock(&lock);

        espera_thread(30);
    }
    return NULL;
}
void* thread_Consumidora(void*){
    Matrix y = newMatrix(3, 1);
    for(double t = 0.0; t <= tempo; t+=intervalo){
        pthread_mutex_lock(&lock);
        matriz_estado_X = calcula_proximo_estado(matriz_estado_B, matriz_entrada);
        atualiza_matriz_B(matriz_estado_B, matriz_estado_X);
        y = calcula_sinal_de_saida(matriz_estado_C, matriz_estado_X);
        imprimi_resultado(t, matriz_entrada, y);
        pthread_mutex_unlock(&lock);

        espera_thread(50);
    }
    return NULL;
}

void inicializa_Matriz(){
    matriz_estado_X= newMatrix(3, 1);
    matriz_estado_B = newMatrix(3, 2);
    matriz_estado_C = newMatrix(3, 3);

    matriz_entrada = newMatrix(2, 1);
   

    matriz_estado_X.matriz[0][0] = 0;
    matriz_estado_X.matriz[1][0] = 0;
    matriz_estado_X.matriz[2][0] = 0;

    matriz_estado_B.matriz[0][0] = sin(matriz_estado_X.matriz[2][0]);
    matriz_estado_B.matriz[0][1] = 0;
    matriz_estado_B.matriz[1][0] = cos(matriz_estado_X.matriz[2][0]);
    matriz_estado_B.matriz[1][1] = 0;
    matriz_estado_B.matriz[2][0] = 0;
    matriz_estado_B.matriz[2][1] = 1;


    matriz_estado_C.matriz[0][0] = 0.5 * D * cos(matriz_estado_X.matriz[2][0]);
    matriz_estado_C.matriz[0][1] = 0;
    matriz_estado_C.matriz[0][2] = 0;
    matriz_estado_C.matriz[1][0] = 0;
    matriz_estado_C.matriz[1][1] = 0.5 * D * cos(matriz_estado_X.matriz[2][0]);
    matriz_estado_C.matriz[1][2] = 0;
    matriz_estado_C.matriz[2][0] = 0;
    matriz_estado_C.matriz[2][1] = 0;
    matriz_estado_C.matriz[2][2] = 1;
    
}

int main(){
    pthread_t t1;
    pthread_t t2;

    inicializa_Matriz();
 
    pthread_create(&t1, NULL, thread_Produtora, NULL); 
    pthread_create(&t2, NULL, thread_Consumidora, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    freeMatrix(matriz_estado_B, matriz_estado_C, matriz_estado_X, matriz_entrada, NULL);

    return 0;
}