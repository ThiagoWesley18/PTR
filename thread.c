#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int arg1;
    int arg2;
} args_t;

void* func1(void* arg){
    
    args_t i = *(args_t*)arg;
    i.arg1++;
    *(args_t*)arg = i;
    return NULL;
}

void* func2(void* arg){
    int i = *(int*)arg;
    printf("func%d...\n",i);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t t1;
    args_t args;
    args.arg1 = 1;
    args.arg2 = 2;

    while (1)
    {
        pthread_create(&t1, NULL, func1, &args);
        sleep(1);
        printf("func%d...\n",args.arg1);
        //pthread_create(&t2, NULL, func2, &arg2);

    }
    
    return 0;
}