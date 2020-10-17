//
// Created by simpl on 17-10-2020.
//

#include "electric.h"
#include <errno.h>
#include <unistd.h>
void *electricLive(void * input){
    int id = *(int *) input;
    struct timespec waitTime;
    timespec_get(&waitTime, TIMER_ABSTIME);
    waitTime.tv_sec += t;
    int res = sem_timedwait(&electricStages,&waitTime);
    int temp;
//    printf("%lld.%.9ld", (long long)waitTime.tv_sec, waitTime.tv_nsec);
    sem_getvalue(&acousticStages, &temp);
//    if(res != -1) printf("%s decreased electric sema \n", people[id].name);
    pthread_mutex_lock(&personMutex[id]);
    if(res == -1 && errno == ETIMEDOUT ){
        if( people[id].status == WAITING_TO_PERFORM) {
            printf(COL_MAGENTA "%s has ran out of patience and left. sem  = %d :(\n" COL_RESET, people[id].name, temp);
            people[id].status = EXITED;
            pthread_mutex_unlock(&personMutex[id]);
            return NULL;
        }
        else {
            pthread_mutex_unlock(&personMutex[id]);
            return NULL;
        }
    }

    if(people[id].status != WAITING_TO_PERFORM){
        sem_post(&electricStages);
//        printf("%s increasing semaphore electric\n" , people[id].name);
        pthread_mutex_unlock(&personMutex[id]);
        return NULL;
    }
    printf(COL_ORANGE "%s performing %c at electric stage for %d seconds\n" COL_RESET, people[id].name, people[id].instrument, people[id].performanceTime);
    people[id].status = PERF_SOLO;
    pthread_mutex_unlock(&personMutex[id]);

    sleep(people[id].performanceTime);

    int flagExtend = 0;
    pthread_mutex_lock(&personMutex[id]) ;
    if (people[id].status == PERF_WITH_OTHER) {
        flagExtend = 1;
    }
    pthread_mutex_unlock(&personMutex[id]);

    if(flagExtend) sleep(2);
    printf(COL_BLUE "%s performance with %c at electric stage has ended\n" COL_RESET, people[id].name, people[id].instrument);
    people[id].status = WAITING_FOR_TSHIRT;
    if(people[id].singerId != -1){
        people[people[id].singerId].status = WAITING_FOR_TSHIRT;
    }
    sem_post(&electricStages);



    printf(COL_DARK_MAGENTA "%s waiting to collect tshirt. \n" COL_RESET, people[id].name);
    sem_wait(&tshirtQueue);
    printf(COL_DARK_MAGENTA "%s is collecting tshirt. \n" COL_RESET, people[id].name);
    people[id].status = COLLECTING_TSHIRT;
    sleep(2);
    sem_post(&tshirtQueue);
    people[id].status = EXITED;
    return NULL;
}