#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include "simulacaoLib.h"
#define intervalo 0.1
#define tempo_inicio 0.00
#define tempo 20.0
#define D 0.6

typedef struct {
    Matrix matriz_estado_B;
    Matrix matriz_estado_C;
    Matrix matriz_estado_D;
    Matrix matriz_estado_X;
    Matrix matriz_u;
    sem_t sem_produtor;
    sem_t sem_consumidor;
    pthread_mutex_t lock;
} Monitor;
Monitor monitor;


void* thread_Produtora(void* arg){
    (void)arg;
    for(double t = tempo_inicio; t <= tempo; t+=intervalo){
        
        // Verifica se pode produzir, se pode, decrementa o semáforo e faz o lock dos recursos
        sem_wait(&monitor.sem_produtor);
        pthread_mutex_lock(&monitor.lock);

        Array uk = calcula_sinal_de_entrada(t); 
        monitor.matriz_u.matriz[0][0] = uk.in[0];
        monitor.matriz_u.matriz[1][0] = uk.in[1];
        monitor.matriz_estado_X = calcula_proximo_estado(monitor.matriz_estado_B, monitor.matriz_u);
    
        // Libera o lock e incrementa o semáforo consumidor para indicar que o recurso está disponível
        pthread_mutex_unlock(&monitor.lock);
        sem_post(&monitor.sem_consumidor);

        espera_thread(30);
    }
    return NULL;
}
void* thread_Consumidora(void*  arg){
    (void)arg;
    Matrix y = newMatrix(3, 1);
    for(double t = tempo_inicio; t <= tempo; t+=intervalo){
        // trava a thread até que o semáforo consumidor seja liberado pelo sem_post do produtor
        sem_wait(&monitor.sem_consumidor);
        pthread_mutex_lock(&monitor.lock);

        integral_matriz_X(monitor.matriz_estado_X); // novo x
        atualiza_matriz_B(monitor.matriz_estado_B, monitor.matriz_estado_X); // atualiza a matriz B com o novo x
        atualiza_matriz_D(monitor.matriz_estado_D, monitor.matriz_estado_X, D); // atualiza a matriz D com o novo x

        y = calcula_sinal_de_saida(monitor.matriz_estado_C, monitor.matriz_estado_X, monitor.matriz_estado_D);
        imprimi_resultado(t, monitor.matriz_u, y);

        // Libera o lock e incrementa o semáforo produtor para liberar o recurso
        pthread_mutex_unlock(&monitor.lock);
        sem_post(&monitor.sem_produtor);
        espera_thread(50);
    }
    return NULL;
}

void inicializa_Matriz(){
    sem_init(&monitor.sem_produtor, 0, 5);
    sem_init(&monitor.sem_consumidor, 0, 0);

    monitor.matriz_estado_X= newMatrix(3, 1);
    monitor.matriz_estado_B = newMatrix(3, 2);
    monitor.matriz_estado_C = newMatrix(2, 3);
    monitor.matriz_estado_D = newMatrix(2, 1);

    monitor.matriz_u = newMatrix(2, 1);

    monitor.matriz_estado_X.matriz[0][0] = 0;
    monitor.matriz_estado_X.matriz[1][0] = 0;
    monitor.matriz_estado_X.matriz[2][0] = 0;

    monitor.matriz_estado_B.matriz[0][0] = sin(monitor.matriz_estado_X.matriz[2][0]);
    monitor.matriz_estado_B.matriz[0][1] = 0;
    monitor.matriz_estado_B.matriz[1][0] = cos(monitor.matriz_estado_X.matriz[2][0]);
    monitor.matriz_estado_B.matriz[1][1] = 0;
    monitor.matriz_estado_B.matriz[2][0] = 0;
    monitor.matriz_estado_B.matriz[2][1] = 1;

    monitor.matriz_estado_C.matriz[0][0] = 1;
    monitor.matriz_estado_C.matriz[0][1] = 0;
    monitor.matriz_estado_C.matriz[0][2] = 0;
    monitor.matriz_estado_C.matriz[1][0] = 0;
    monitor.matriz_estado_C.matriz[1][1] = 1;
    monitor.matriz_estado_C.matriz[1][2] = 0;

    monitor.matriz_estado_D.matriz[0][0] = (D/2) * cos(monitor.matriz_estado_X.matriz[2][0]);
    monitor.matriz_estado_D.matriz[1][0] = (D/2) * sin(monitor.matriz_estado_X.matriz[2][0]);
}

int main(){
    pthread_t t1;
    pthread_t t2;

    // Inicializa o mutex
    pthread_mutex_init(&monitor.lock, NULL);

    inicializa_Matriz();
 
    pthread_create(&t1, NULL, thread_Produtora, NULL); 
    pthread_create(&t2, NULL, thread_Consumidora, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&monitor.sem_produtor);
    sem_destroy(&monitor.sem_consumidor);

    freeMatrix(monitor.matriz_estado_B, monitor.matriz_estado_C, monitor.matriz_estado_X, monitor.matriz_u, NULL);

    return 0;
}