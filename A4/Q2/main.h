//
// Created by simpl on 15-10-2020.
//

#ifndef Q2_MAIN_H
#define Q2_MAIN_H
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <memory.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/shm.h>

#define COL_RESET "\x1B[0m"
#define COL_RED "\x1B[31m"
#define COL_GREEN "\x1B[32m"
#define COL_BLUE "\x1b[34m"
#define COL_MAGENTA "\x1b[35m"
#define COL_CYAN "\x1b[36m"

struct pharma {
    int id;
    int productionTime; //w
    int numBatchesProduced; //r
    int batchStrength; //p
    float probSuccess; //x
    int availBatches;
};

struct zone {
    int id;
    int vaccinesLeft;
    int numSlots;
    int companyId;
    int occupiedSlots;
    int *studentIds;
};

enum State {
    CANDIDATE,
    WAITING,
    ADMITTED,
    FAILED
};

struct student {
    int id;
    enum State progressState;
    int numTries;
};


pthread_mutex_t *zoneMutexes;

int num_companies, num_zones, num_students, studentsLeft;

struct student **studentArray;
struct zone **zonesArray;
struct pharma **pharmaArray;

int min(int a, int b);
int randomCustom(int l, int r);
#endif //Q2_MAIN_H
