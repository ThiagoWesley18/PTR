#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include "simulacaoLib.h"
#define intervalo 0.1
#define tempo_inicio 0.00
#define tempo 20.0
#define D 1.0

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_produtor;
sem_t sem_consumidor;

// Variaveis globais
Matrix matriz_estado_B;
Matrix matriz_estado_C;
Matrix matriz_estado_X;
Matrix matriz_u;

void* thread_Produtora(void* arg){
    (void)arg;
    for(double t = tempo_inicio; t <= tempo; t+=intervalo){
        
        // Verifica se pode produzir, se pode, decrementa o semáforo e faz o lock dos recursos
        sem_wait(&sem_produtor);
        pthread_mutex_lock(&lock);

        Array uk = calcula_sinal_de_entrada(t); 
        matriz_u.matriz[0][0] = uk.in[0];
        matriz_u.matriz[1][0] = uk.in[1];
        matriz_estado_X = calcula_proximo_estado(matriz_estado_B, matriz_u);
    
        // Libera o lock e incrementa o semáforo consumidor para indicar que o recurso está disponível
        pthread_mutex_unlock(&lock);
        sem_post(&sem_consumidor);

        espera_thread(30);
    }
    return NULL;
}
void* thread_Consumidora(void*  arg){
    (void)arg;
    Matrix y = newMatrix(3, 1);
    for(double t = tempo_inicio; t <= tempo; t+=intervalo){
        // trava a thread até que o semáforo consumidor seja liberado pelo sem_post do produtor
        sem_wait(&sem_consumidor);
        pthread_mutex_lock(&lock);

        y = calcula_sinal_de_saida(matriz_estado_C, matriz_estado_X);
        atualiza_matriz_B(matriz_estado_B, y); // atualiza a matriz B com o novo x
        imprimi_resultado(t, matriz_u, y);

        // Libera o lock e incrementa o semáforo produtor para liberar o recurso
        pthread_mutex_unlock(&lock);
        sem_post(&sem_produtor);
        espera_thread(50);
    }
    return NULL;
}

void inicializa_Matriz(){
    sem_init(&sem_produtor, 0, 5);
    sem_init(&sem_consumidor, 0, 0);

    matriz_estado_X= newMatrix(3, 1);
    matriz_estado_B = newMatrix(3, 2);
    matriz_estado_C = newMatrix(3, 3);

    matriz_u = newMatrix(2, 1);

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

    sem_destroy(&sem_produtor);
    sem_destroy(&sem_consumidor);

    freeMatrix(matriz_estado_B, matriz_estado_C, matriz_estado_X, matriz_u, NULL);

    return 0;
}