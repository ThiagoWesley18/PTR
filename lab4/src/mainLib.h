#ifndef MAIN_H__
#define MAIN_H__

#include <pthread.h>


typedef struct {
    void *ref;
    void *saida;
    void *buffer; 
} thread_args_t;




#endif //MAIN_H__