#ifndef DISPLAY_H__
#define DISPLAY_H__

#define MAX_STR_SIZE 256
#define SHM_NAME "/buffer"


void *display_print(void *arg);

typedef struct {
    char linha[MAX_STR_SIZE];
} BufferCompartilhado;


#endif //DISPLAY_H__