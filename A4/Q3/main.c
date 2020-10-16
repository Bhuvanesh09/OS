#include <stdio.h>
#include <unistd.h>
#include "main.h"
void *shareMem(size_t size) {
    key_t mem_key = IPC_PRIVATE;
    // get shared memory of this much size and with this private key
    // what is 0666?
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);
    // attach the address space of shared memory to myself (callee)
    return (void *)shmat(shm_id, NULL, 0);
}
int randomCustom(int l, int r) {
    return rand() % (r - l + 1) + l;
}
int main() {
    scanf("%d %d %d %d %d %d %d", &k, &a, &e, &c, &t1, &t2, &t);
    waitTime.tv_nsec = 0;
    waitTime.tv_sec = t;
    people = (struct person *) shareMem(sizeof(struct person) * k);
    int maxTime = 0, numSingers = 0;
    for(int i=0; i<k; i++){
        people[i].name = (char *) shareMem(sizeof(char) * 1000);
        people[i].id = i;
        scanf("%s %c %d", people[i].name, &people[i].instrument, &people[i].arrivalTime);
        people[i].status = NOT_YET_ARRIVED;
        people[i].isSinger = people[i].instrument == 's' ? 1 : 0;
        people[i].performanceTime = randomCustom(t1, t2);
        numSingers += people[i].isSinger;
        maxTime = maxTime > people[i].arrivalTime ? maxTime : people[i].arrivalTime;
    }

    pthread_t *personThreadAcoustic = (pthread_t *) shareMem(sizeof(pthread_t) * k);
    pthread_t *personThreadElectric = (pthread_t *) shareMem(sizeof(pthread_t) * k);
    pthread_t *personThreadSinger = (pthread_t *) shareMem(sizeof(pthread_t) * k);
    personMutex = (pthread_mutex_t *) shareMem(sizeof(pthread_mutex_t) * k);

    sem_init(&acousticStages, NULL, a);
    sem_init(&electricStages, NULL, e) ;
    sem_init(&singerQueue, NULL, a+e);
    sem_init(&tshirtQueue, NULL, c);
    for(int i=0; i < maxTime+1; i++){
        for(int j=0; j<k ; j++){

            if(people[j].arrivalTime == i){
                //initiate mutex
                pthread_mutex_init(&personMutex[j], NULL);
                //start threads here
                printf(COL_LIGHT_GREEN "%s %c just arrived\n" COL_RESET, people[j].name, people[j].instrument);
                people[j].status = WAITING_TO_PERFORM;
                pthread_create(&personThreadAcoustic[j],NULL, acousticLive, &(people[j].id));
            }
        }
        sleep(1);
    }

    //join all threads here;
    for(int i=0; i<k; i++){
        pthread_join(personThreadAcoustic[i], NULL);
    }

    return 0;
}
