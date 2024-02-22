#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "simulacaoLib.h"
#define intervalo 0.1
#define tempo 20.0
#define D 1.0

pthread_mutex_t lock;

// Variaveis globais
Matrix B;
Matrix C;
Matrix x;
Matrix u;

void* thread_1(void*){
    for(double t = 0.0; t <= tempo; t+=intervalo){
        pthread_mutex_lock(&lock);
        Array v = entrada(t);

        u.matriz[0][0] = v.in[0];
        u.matriz[1][0] = v.in[1];
        pthread_mutex_unlock(&lock);

        usleep(30);
    }
    return NULL;
}
void* thread_2(void*){
    Matrix y = newMatrix(3, 1);
    for(double t = 0.0; t <= tempo; t+=intervalo){
        pthread_mutex_lock(&lock);
        x = estado(B, u);
        atualizaB(B, x);
        y = saida(C, x);
        resultado(t, u, y);
      
        pthread_mutex_unlock(&lock);

        usleep(50);
    }
    return NULL;
}

void inicializa(){
    x= newMatrix(3, 1);
    B = newMatrix(3, 2);
    C = newMatrix(3, 3);

    u = newMatrix(2, 1);
   

    x.matriz[0][0] = 0;
    x.matriz[1][0] = 0;
    x.matriz[2][0] = 0;

    B.matriz[0][0] = sin(x.matriz[2][0]);
    B.matriz[0][1] = 0;
    B.matriz[1][0] = cos(x.matriz[2][0]);
    B.matriz[1][1] = 0;
    B.matriz[2][0] = 0;
    B.matriz[2][1] = 1;


    C.matriz[0][0] = 0.5 * D * cos(x.matriz[2][0]);
    C.matriz[0][1] = 0;
    C.matriz[0][2] = 0;
    C.matriz[1][0] = 0;
    C.matriz[1][1] = 0.5 * D * cos(x.matriz[2][0]);
    C.matriz[1][2] = 0;
    C.matriz[2][0] = 0;
    C.matriz[2][1] = 0;
    C.matriz[2][2] = 1;
    
}

int main(){
    pthread_t t1;
    pthread_t t2;

    inicializa();
 
    pthread_create(&t1, NULL, thread_1, NULL); 
    pthread_create(&t2, NULL, thread_2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    freeMatrix(B, C, x, u, NULL);

    return 0;
}