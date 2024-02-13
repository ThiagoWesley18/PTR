#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulacaoLib.h"

void simula(Matrix B, Matrix C){
    Matrix u = newMatrix(2, 1);
    Matrix y = newMatrix(3, 1);
    Matrix Estado = newMatrix(3, 1);

    double intervalo = 0.1;
    double tempo = 20.0;
    
    // Faz a simulação no range de tempo de 0 a 20 segundos com intervalo de 0.1 segundos(100ms)
    for(double t = 0.0; t <= tempo; t+=intervalo){
        // sinal de entrada no instante de tempo t
        Array v = entrada(t);
        
        // Matriz do espaço de estados do robô refente a entrada no instante de tempo t
        u.matriz[0][0] = v.in[0];
        u.matriz[1][0] = v.in[1];
        
        // Atualiza o estado do robô
        Estado = estado(B, u);

        // Atualiza a saída do robô
        y = saida(C, Estado);

        // Imprime o resultado da simulação
        resultado(t, u, y);
    }
}

int main(){
    // Matrizes do espaço de estados do robô
    Matrix B = newMatrix(3, 2);
    Matrix C = newMatrix(3, 3);
    Matrix x = newMatrix(3, 1);

    x.matriz[0][0] = 0;
    x.matriz[1][0] = 0;
    x.matriz[2][0] = 0;

    B.matriz[0][0] = sin(x.matriz[2][0]);
    B.matriz[0][1] = 0;
    B.matriz[1][0] = cos(x.matriz[2][0]);
    B.matriz[1][1] = 0;
    B.matriz[2][0] = 0;
    B.matriz[2][1] = 1;

    C.matriz[0][0] = 1;
    C.matriz[0][1] = 0;
    C.matriz[0][2] = 0;
    C.matriz[1][0] = 0;
    C.matriz[1][1] = 1;
    C.matriz[1][2] = 0;
    C.matriz[2][0] = 0;
    C.matriz[2][1] = 0;
    C.matriz[2][2] = 1;

    // Faz a simulação passando as matrizes do espaço de estados do robô
    simula(B, C);

    return 0;
}