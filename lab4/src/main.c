#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
	printf("t,x1,x2,teta,xref,yref\n");
    pthread_t controle_thr;
    pthread_t linearizaçao_thr;
    pthread_t simulaçao_thr;
    pthread_t direçao_thr;
    pthread_t referencia_thr;
    pthread_t display_thr;
    

    SharedMemoRef shared, *shmRef = &shared;
    SharedMemoSaida sharedS, *shmSaida = &sharedS;

    thread_args_t args;
    args.ref = shmRef;
    args.saida = shmSaida;
    
    monitoRef_init(args.ref);
    monitoSaida_init(args.saida);

    pthread_create(&referencia_thr, NULL, uthread, &args);
    pthread_create(&direçao_thr, NULL, dir, &args);
    pthread_create(&controle_thr, NULL, controle, &args);
    pthread_create(&linearizaçao_thr, NULL, linearizaçao, &args);
    pthread_create(&simulaçao_thr, NULL, robo, &args);
    pthread_create(&display_thr, NULL, display_print, &args);

    pthread_join(referencia_thr, NULL);
    pthread_join(direçao_thr, NULL);
    pthread_join(simulaçao_thr, NULL);
    pthread_join(linearizaçao_thr, NULL);
    pthread_join(controle_thr, NULL);
    pthread_join(display_thr, NULL);

    
    monitoRef_destroy(args.ref);
    monitoSaida_destroy(args.saida);

    return EXIT_SUCCESS;
}