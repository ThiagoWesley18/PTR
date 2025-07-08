#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "monitorRef.h"

void monitoRef_init(SharedMemoRef *shm) {
	*shm = (SharedMemoRef){0};
    shm->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void monitoRef_destroy(SharedMemoRef *shm) {
    pthread_mutex_destroy(&(shm->mutex));
	*shm = (SharedMemoRef){0};
}

// Referencia
void set_xref(SharedMemoRef *shm, double xref) {
    pthread_mutex_lock(&(shm->mutex));
        shm->xref = xref;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_xref(SharedMemoRef *shm) {
    double xref;
    pthread_mutex_lock(&(shm->mutex));
        xref = shm->xref;
    pthread_mutex_unlock(&(shm->mutex));
    return xref;
}
void set_yref(SharedMemoRef *shm, double yref) {
    pthread_mutex_lock(&(shm->mutex));
        shm->yref = yref;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_yref(SharedMemoRef *shm) {
    double yref;
    pthread_mutex_lock(&(shm->mutex));
        yref = shm->yref;
    pthread_mutex_unlock(&(shm->mutex));
    return yref;
}

// Modelo Referencia 
void set_Ymx(SharedMemoRef *shm, double Ymx) {
    pthread_mutex_lock(&(shm->mutex));
        shm->Ymx = Ymx;
    pthread_mutex_unlock(&(shm->mutex));
}

double get_Ymx(SharedMemoRef *shm) {
    double Ymx;
    pthread_mutex_lock(&(shm->mutex));
        Ymx = shm->Ymx;
    pthread_mutex_unlock(&(shm->mutex));
    return Ymx;
}
void set_Ymy(SharedMemoRef *shm, double Ymy) {
    pthread_mutex_lock(&(shm->mutex));
        shm->Ymy = Ymy;
    pthread_mutex_unlock(&(shm->mutex));
}

double get_Ymy(SharedMemoRef *shm) {
    double Ymy;
    pthread_mutex_lock(&(shm->mutex));
        Ymy = shm->Ymy;
    pthread_mutex_unlock(&(shm->mutex));
    return Ymy;
}
