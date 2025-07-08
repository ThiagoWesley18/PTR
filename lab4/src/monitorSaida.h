#ifndef MONITORSAIDA_H__
#define MONITORSAIDA_H__

#include <pthread.h>
#define R 0.3


typedef struct { 
    // Controle
    double vx;
    double vy;

    // Linearizacao
    double u1;
    double u2;

    // Robo
    double y1;
    double y2;
    double x3;

    pthread_mutex_t mutex;
} SharedMemoSaida;

void monitoSaida_init(SharedMemoSaida *shm);
void monitoSaida_destroy(SharedMemoSaida*shm);

// Controle
void set_vx(SharedMemoSaida *shm, double v);
double get_vx(SharedMemoSaida *shm);

void set_vy(SharedMemoSaida *shm, double v);
double get_vy(SharedMemoSaida *shm);

// Linearizacao
void set_u1(SharedMemoSaida *shm, double u);
double get_u1(SharedMemoSaida *shm);
void set_u2(SharedMemoSaida *shm, double u);
double get_u2(SharedMemoSaida *shm);

// Robo
void set_y1(SharedMemoSaida *shm, double y);
double get_y1(SharedMemoSaida *shm);
void set_y2(SharedMemoSaida *shm, double y);
double get_y2(SharedMemoSaida *shm);

void set_x3(SharedMemoSaida *shm, double x);
double get_x3(SharedMemoSaida *shm);


#endif //MONITORSAIDA_H__