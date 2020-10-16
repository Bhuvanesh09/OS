//
// Created by simpl on 17-10-2020.
//

#include <errno.h>
#include <errno.h>
#include <unistd.h>
#include "acoustic.h"
void *acousticLive(void * input){
    int id = *(int *) input;
    int res = sem_timedwait(&acousticStages,&waitTime);
    if(res == -1 && errno == ETIMEDOUT && people[id].status == WAITING_TO_PERFORM){
        printf(COL_MAGENTA "%s has ran out of patience and left. :(\n" COL_RESET, people[id].name);
        people[id].status = EXITED;
        return NULL;
    }

    pthread_mutex_lock(&personMutex[id]);
    if(people[id].status != WAITING_TO_PERFORM){
        sem_post(&acousticStages);
        pthread_mutex_unlock(&personMutex[id]);
        return NULL;
    }
    pthread_mutex_unlock(&personMutex[id]);

    printf(COL_ORANGE "%s performing %c at acoustic stage for %d seconds\n" COL_RESET, people[id].name, people[id].instrument, people[id].performanceTime);
    people[id].status = PERF_SOLO;
    sleep(people[id].performanceTime);

    printf(COL_BLUE "%s performance with %c at acoustic stage has ended\n" COL_RESET, people[id].name, people[id].instrument);
    sem_post(&acousticStages);

    sem_wait(&tshirtQueue);
    sleep(2);

    printf(COL_DARK_MAGENTA "%s is collecting tshirt. \n" COL_RESET, people[id].name);
    sem_post(&tshirtQueue);
    return NULL;
}
