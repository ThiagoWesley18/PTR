#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simulacaoLib.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// Calcula o estado seguinte do robô
Matrix calcula_proximo_estado(Matrix matriz_estado_B, Matrix matriz_u){
    return multMatrix(matriz_estado_B, matriz_u);
}

// Calcula a saída do robô
Matrix calcula_sinal_de_saida(Matrix matriz_estado_C, Matrix matriz_estado_X){
    return sumMatrix(matriz_estado_X, multMatrix(matriz_estado_C, matriz_estado_X));
}

// Calcula a entrada do robô no instante de tempo t
Array calcula_sinal_de_entrada(double t){
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

void  integral_matriz_X(Matrix matriz_estado_X){
    matriz_estado_X.matriz[0][0] = cos(matriz_estado_X.matriz[0][0]);
    matriz_estado_X.matriz[1][0] = -1*sin(matriz_estado_X.matriz[0][0]);
    matriz_estado_X.matriz[2][0] = 0;
}
void atualiza_matriz_B(Matrix matriz_estado_B, Matrix matriz_estado_X){

    matriz_estado_B.matriz[0][0] = sin(matriz_estado_X.matriz[2][0]);
    matriz_estado_B.matriz[0][1] = 0;
    matriz_estado_B.matriz[1][0] = cos(matriz_estado_X.matriz[2][0]);
    matriz_estado_B.matriz[1][1] = 0;
    matriz_estado_B.matriz[2][0] = 0;
    matriz_estado_B.matriz[2][1] = 1;
}

void espera_thread(int milisegundos){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = milisegundos * 1000000; 
    nanosleep(&ts, NULL);
}

// Imprime o resultado da simulação
void imprimi_resultado(double t, Matrix matriz_u, Matrix y) {
    static int first_call = 1;
    
    // Abrir o arquivo no modo de escrita na primeira chamada para apagar o conteúdo existente
    // Abrir o arquivo no modo de anexação nas chamadas subsequentes para adicionar novos dados
    FILE* file = fopen("resultado.txt", first_call ? "w" : "a");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo resultado.txt\n");
        return;
    }

    fprintf(file, "%lf    [%lf    %lf]    [%lf    %lf    %lf]\n", t, matriz_u.matriz[0][0], matriz_u.matriz[1][0], y.matriz[0][0], y.matriz[1][0], y.matriz[2][0]);

    fclose(file);

    // Resetar a flag first_call para que o arquivo seja aberto no modo de anexação nas chamadas subsequentes
    first_call = 0; 
}