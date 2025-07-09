#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "monitorSaida.h"

void monitoSaida_init(SharedMemoSaida *shm) {
	*shm = (SharedMemoSaida){0};
    shm->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void monitoSaida_destroy(SharedMemoSaida *shm) {
    pthread_mutex_destroy(&(shm->mutex));
	*shm = (SharedMemoSaida){0};
}

// Controle
void set_vx(SharedMemoSaida *shm, double vx) {
    pthread_mutex_lock(&(shm->mutex));
        shm->vx = vx;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_vx(SharedMemoSaida *shm) {
    double vx;
    pthread_mutex_lock(&(shm->mutex));
        vx = shm->vx;
    pthread_mutex_unlock(&(shm->mutex));
    return vx;
}

void set_vy(SharedMemoSaida *shm, double vy) {
    pthread_mutex_lock(&(shm->mutex));
        shm->vy = vy;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_vy(SharedMemoSaida *shm) {
    double vy;
    pthread_mutex_lock(&(shm->mutex));
        vy = shm->vy;
    pthread_mutex_unlock(&(shm->mutex));
    return vy;
}

// Linearizacao
void set_u1(SharedMemoSaida *shm, double u1) {
    pthread_mutex_lock(&(shm->mutex));
        shm->u1 = u1;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_u1(SharedMemoSaida *shm) {
    double u1;
    pthread_mutex_lock(&(shm->mutex));
        u1 = shm->u1;
    pthread_mutex_unlock(&(shm->mutex));
    return u1;
}
void set_u2(SharedMemoSaida *shm, double u2) {
    pthread_mutex_lock(&(shm->mutex));
        shm->u2 = u2;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_u2(SharedMemoSaida *shm) {
    double u2;
    pthread_mutex_lock(&(shm->mutex));
        u2 = shm->u2;
    pthread_mutex_unlock(&(shm->mutex));
    return u2;
}

// Robo
void set_y1(SharedMemoSaida *shm, double y1) {
    pthread_mutex_lock(&(shm->mutex));
        shm->y1 = y1;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_y1(SharedMemoSaida *shm) {
    double y1;
    pthread_mutex_lock(&(shm->mutex));
        y1 = shm->y1;
    pthread_mutex_unlock(&(shm->mutex));
    return y1;
}

void set_y2(SharedMemoSaida *shm, double y2) {
    pthread_mutex_lock(&(shm->mutex));
        shm->y2 = y2;
    pthread_mutex_unlock(&(shm->mutex));
}

double get_y2(SharedMemoSaida *shm) {
    double y2;
    pthread_mutex_lock(&(shm->mutex));
        y2 = shm->y2;
    pthread_mutex_unlock(&(shm->mutex));
    return y2;
}

void set_x3(SharedMemoSaida *shm, double x3) {
    pthread_mutex_lock(&(shm->mutex));
        shm->x3 = x3;
    pthread_mutex_unlock(&(shm->mutex));
}
double get_x3(SharedMemoSaida *shm) {
    double x3;
    pthread_mutex_lock(&(shm->mutex));
        x3 = shm->x3;
    pthread_mutex_unlock(&(shm->mutex));
    return x3;
}