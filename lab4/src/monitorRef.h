#ifndef MONITOREF_H__
#define MONITOREF_H__

#include <pthread.h>
#define a1 3
#define a2 3


typedef struct { 
    // Referencia
    double xref;
    double yref;

    // Modelo Referencia
    double Ymx;
    double Ymy;

    pthread_mutex_t mutex;
} SharedMemoRef;

void monitoRef_init(SharedMemoRef *shm);
void monitoRef_destroy(SharedMemoRef *shm);

// Referencia
void set_xref(SharedMemoRef *shm, double xref);
double get_xref(SharedMemoRef *shm);
void set_yref(SharedMemoRef *shm, double yref);
double get_yref(SharedMemoRef *shm);

// Modelo Referencia
void set_Ymx(SharedMemoRef *shm, double ymx);
double get_Ymx(SharedMemoRef *shm);

void set_Ymy(SharedMemoRef *shm, double ymy);
double get_Ymy(SharedMemoRef *shm);


#endif //MONITOREF_H__