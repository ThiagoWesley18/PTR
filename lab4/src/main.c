#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include "monitorRef.h"
#include "monitorSaida.h"
#include "display.h"
#include "controle.h"
#include "linearizaçao.h"
#include "simulaçao.h"
#include "direçao.h"
#include "referencia.h"
#include "mainLib.h"

//int main(int argc, char *argv[])
int main()
{
    //printf("t,x1,x2,teta,xref,yref\n");
    pthread_t controle_thr;
    pthread_t linearizaçao_thr;
    pthread_t simulaçao_thr;
    pthread_t direçao_thr;
    pthread_t referencia_thr;
    pthread_t display_thr;
    struct timespec start, end;
    double elapsed_time;
    
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (ftruncate(fd, sizeof(BufferCompartilhado)) == -1) {
        perror("Erro ao truncar a memória compartilhada");
        close(fd);
        return EXIT_FAILURE;
    }
    
    SharedMemoRef shared, *shmRef = &shared;
    SharedMemoSaida sharedS, *shmSaida = &sharedS;
    BufferCompartilhado *shmBuffer = mmap(NULL, sizeof(BufferCompartilhado), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    thread_args_t args;
    args.ref = shmRef;
    args.saida = shmSaida;
    args.buffer = shmBuffer;
    
    monitoRef_init(args.ref);
    monitoSaida_init(args.saida);
    

    pthread_create(&display_thr, NULL, display_print, &args);

    // Captura o tempo antes de iniciar as threads
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    pthread_create(&referencia_thr, NULL, uthread, &args);
    pthread_create(&direçao_thr, NULL, dir, &args);
    pthread_create(&controle_thr, NULL, controle, &args);
    pthread_create(&linearizaçao_thr, NULL, linearizaçao, &args);
    pthread_create(&simulaçao_thr, NULL, robo, &args);

    pthread_join(referencia_thr, NULL);
    pthread_join(direçao_thr, NULL);
    pthread_join(simulaçao_thr, NULL);
    pthread_join(linearizaçao_thr, NULL);
    pthread_join(controle_thr, NULL);
    
    // Captura o tempo após a execução das threads
    clock_gettime(CLOCK_MONOTONIC, &end);
    // Calcula o tempo decorrido em segundos
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Tempo total de execução das threads: %.6f segundos\n\n", elapsed_time);

    pthread_join(display_thr, NULL);


    monitoRef_destroy(args.ref);
    monitoSaida_destroy(args.saida);
    
    return EXIT_SUCCESS;
}

