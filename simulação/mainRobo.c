#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include "simulacaoLib.h"

Matrix simula(Matrix B, Matrix u, Array v){   
    // Matriz do espaço de estados do robô refente a entrada no instante de tempo t
    u.matriz[0][0] = v.in[0];
    u.matriz[1][0] = v.in[1];
    
    return estado(B, u);  
}

void* thread_1(void* agr){
    // sinal de entrada no instante de tempo t
    Array v = entrada(((args_th1*)agr)->t);
    // Faz a simulação passando as matrizes do espaço de estados do robô
    ((args_th1*)agr)->Estado = simula(((args_th1*)agr)->B, ((args_th1*)agr)->u, v);

    // Vai exercutar a cada 30ms
    usleep(30000);
    return NULL;
}

void* thread_2(void* agr){
    // Atualiza o estado do robô
    ((args_th2*)agr)->y = saida(((args_th2*)agr)->C, ((args_th2*)agr)->Estado);
    // Imprime o resultado da simulação
    resultado(((args_th2*)agr)->t, ((args_th2*)agr)->u, ((args_th2*)agr)->y );

    // Vai exercutar a cada 50ms
    usleep(50000);
    return NULL;
}

int main(){
    //Define as Threads e as variáveis de entrada
    args_th1 arg1;
    args_th2 arg2;
    pthread_t t1;
    pthread_t t2;
    // Intervalo de tempo da simulação
    double intervalo = 0.1;
    double tempo = 20.0;
    double D = 1.0;

    // Matrizes do espaço de estados do robô
    Matrix B = newMatrix(3, 2);
    Matrix C = newMatrix(3, 3);
    Matrix x = newMatrix(3, 1);

    Matrix u = newMatrix(2, 1);
    arg1.u = u;
    Matrix y = newMatrix(3, 1);
    arg2.y = y;
    Matrix Estado = newMatrix(3, 1);
    arg1.Estado = Estado;

    x.matriz[0][0] = 0;
    x.matriz[1][0] = 0;
    x.matriz[2][0] = 0;

    B.matriz[0][0] = sin(x.matriz[2][0]);
    B.matriz[0][1] = 0;
    B.matriz[1][0] = cos(x.matriz[2][0]);
    B.matriz[1][1] = 0;
    B.matriz[2][0] = 0;
    B.matriz[2][1] = 1;
    arg1.B = B;

    C.matriz[0][0] = 0.5 * D * cos(x.matriz[2][0]);
    C.matriz[0][1] = 0;
    C.matriz[0][2] = 0;
    C.matriz[1][0] = 0;
    C.matriz[1][1] = 0.5 * D * cos(x.matriz[2][0]);
    C.matriz[1][2] = 0;
    C.matriz[2][0] = 0;
    C.matriz[2][1] = 0;
    C.matriz[2][2] = 1;
    arg2.C = C;

    // Faz a simulação no range de tempo de 0 a 20 segundos com intervalo de 0.1 segundos(100ms)
    for(double t = 0.0; t <= tempo; t+=intervalo){

        arg1.t = t;
        pthread_create(&t1, NULL, thread_1, &arg1); 
        
        arg2.t = t;
        arg2.u = arg1.u;
        arg2.Estado = arg1.Estado;
        pthread_create(&t2, NULL, thread_2, &arg2);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
  
    }

    return 0;
}