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
    return sumMatrix(x, multMatrix(C, x));
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

void atualizaB(Matrix B, Matrix x){

    B.matriz[0][0] = sin(x.matriz[2][0]);
    B.matriz[0][1] = 0;
    B.matriz[1][0] = cos(x.matriz[2][0]);
    B.matriz[1][1] = 0;
    B.matriz[2][0] = 0;
    B.matriz[2][1] = 1;
}



// Imprime o resultado da simulação
void resultado(double t, Matrix u, Matrix y) {
    /*static int first_call = 1;
    
    // Abrir o arquivo no modo de escrita na primeira chamada para apagar o conteúdo existente
    // Abrir o arquivo no modo de anexação nas chamadas subsequentes para adicionar novos dados
    FILE* file = fopen("resultado.txt", first_call ? "w" : "a");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo resultado.txt\n");
        return;
    }

    fprintf(file, "%lf    [%lf    %lf]    [%lf    %lf    %lf]\n", t, u.matriz[0][0], u.matriz[1][0], y.matriz[0][0], y.matriz[1][0], y.matriz[2][0]);

    fclose(file);

    // Resetar a flag first_call para que o arquivo seja aberto no modo de anexação nas chamadas subsequentes
    first_call = 0; 
    */
    printf("%lf    [%lf    %lf]    [%lf    %lf    %lf]\n", t, u.matriz[0][0], u.matriz[1][0], y.matriz[0][0], y.matriz[1][0], y.matriz[2][0]);
}