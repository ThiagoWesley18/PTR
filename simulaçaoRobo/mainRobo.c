#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include "simulacaoLib.h"
#include <time.h>
#define intervalo 0.1
#define tempo_inicio 0.00
#define tempo 20.0
#define D 0.6

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_produtor;
sem_t sem_consumidor;
sem_t sem_saida; 

// Variaveis globais
Matrix matriz_estado_B;
Matrix matriz_estado_C;
Matrix matriz_estado_X;
Matrix matriz_u;
Matrix y;
double tempo_saida = 0.0;
int flag = 1;

void* thread_Saida(){
  
    while (flag == 1){
        sem_wait(&sem_saida);
        pthread_mutex_lock(&lock);
        
        imprimi_resultado(tempo_saida, matriz_u, y);
        
        pthread_mutex_unlock(&lock);
    }
    return NULL; 
}


void* thread_Produtora(){
    
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
    }
    espera_thread(30);
    
    return NULL;
}
void* thread_Consumidora(){

    for(double t = tempo_inicio; t <= tempo; t+=intervalo){
        // trava a thread até que o semáforo consumidor seja liberado pelo sem_post do produtor
        sem_wait(&sem_consumidor);
        pthread_mutex_lock(&lock);

        integral_matriz_X(matriz_estado_X); // calcula nova matriz X
        atualiza_matriz_B(matriz_estado_B, matriz_estado_X); // atualiza a matriz B com o novo x
        y = calcula_sinal_de_saida(matriz_estado_C, matriz_estado_X);
        tempo_saida = t;

        sem_post(&sem_saida); 
        // Libera o lock e incrementa o semáforo produtor para liberar o recurso
        pthread_mutex_unlock(&lock);
        sem_post(&sem_produtor);
    }
    espera_thread(50);
    
    return NULL;
}

void inicializa_Matriz(){
    sem_init(&sem_produtor, 0, 5);
    sem_init(&sem_consumidor, 0, 0);
    sem_init(&sem_saida, 0, 0); 

    matriz_estado_X= newMatrix(3, 1);
    matriz_estado_B = newMatrix(3, 2);
    matriz_estado_C = newMatrix(3, 3);

    matriz_u = newMatrix(2, 1);
    y = newMatrix(3, 1);

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
    struct timeval start, end;

    gettimeofday(&start, NULL);

    pthread_t t1;
    pthread_t t2;
    pthread_t thread_tempo;

    pthread_attr_t attr;
    struct sched_param param;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    param.sched_priority = sched_get_priority_max(SCHED_RR);
    pthread_attr_setschedparam(&attr, &param);

    inicializa_Matriz();

    pthread_create(&thread_tempo, NULL, thread_Saida, NULL ); 
    pthread_create(&t1, &attr, thread_Produtora, NULL ); 
    pthread_create(&t2, &attr, thread_Consumidora, NULL );
    
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    flag = 0;
    sem_post(&sem_saida); 
    pthread_join(thread_tempo, NULL);

    gettimeofday(&end, NULL);

    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Tempo de execução: %ld ms\n", micros/1000);

    sem_destroy(&sem_produtor);
    sem_destroy(&sem_consumidor);
<<<<<<< HEAD:simulação/mainRobo.c

    //freeMatrix(matriz_estado_B, matriz_estado_C, matriz_estado_X, matriz_u, NULL);

=======
    sem_destroy(&sem_saida);
>>>>>>> lab4:simulaçaoRobo/mainRobo.c
    return 0;
}