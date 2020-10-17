//
// Created by simpl on 17-10-2020.
//

#ifndef Q3_MAIN_H
#define Q3_MAIN_H

#include <semaphore.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "acoustic.h"
#include "electric.h"
#include "singer.h"

// state Kinds:
enum states{ NOT_YET_ARRIVED, WAITING_TO_PERFORM, PERF_SOLO, PERF_WITH_OTHER, WAITING_FOR_TSHIRT, COLLECTING_TSHIRT, EXITED };
struct person{
    int id;
    char * name;
    char instrument;
    int arrivalTime;
    int performanceTime;
    int isSinger;
    int singerId;
    enum states status;
};
#define COL_RESET "\x1B[0m"
#define COL_RED "\x1B[31m"
#define COL_ORANGE "\x1B[31;1m"
#define COL_GREEN "\x1B[32m"
#define COL_LIGHT_GREEN "\x1B[32;1m"
#define COL_BLUE "\x1b[34m"
#define COL_MAGENTA "\x1b[35;1m"
#define COL_DARK_MAGENTA "\x1b[35m"
#define COL_CYAN "\x1b[36m"

sem_t acousticStages;
sem_t electricStages;
sem_t singerQueue;
sem_t tshirtQueue;
struct person *people;
pthread_mutex_t *personMutex;

int k, a, e, c, t1, t2, t;

int randomCustom(int l, int r);
#endif //Q3_MAIN_H
