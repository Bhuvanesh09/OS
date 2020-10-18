//
// Created by simpl on 17-10-2020.
//

#include "singer.h"

void * singerLive(void * input){
   int id = * (int *) input;
    int joinedOther = 0;
   // check for musicians performing to join them.
   while(people[id].status == WAITING_TO_PERFORM){
       for(int i=0; i< k; i++){
           pthread_mutex_lock(&personMutex[i]);
           if(people[i].status == PERF_SOLO && people[i].isSinger == 0){
               pthread_mutex_lock(&personMutex[id]);
               people[i].status = PERF_WITH_OTHER;
               people[id].status = PERF_WITH_OTHER;
               people[i].singerId = id;
               printf(COL_GREEN"%s has joined %s's performance, performance exceeded by 2 seconds. \n" COL_RESET, people[id].name, people[i].name);
               pthread_mutex_unlock(&personMutex[id]);
               joinedOther = 1;
           }
           pthread_mutex_unlock(&personMutex[i]);
           if(people[id].status != WAITING_TO_PERFORM) break;
       }
   }

   if(people[id].status != WAITING_TO_PERFORM && joinedOther){
       while(people[id].status != WAITING_FOR_TSHIRT) {};
       printf(COL_DARK_MAGENTA "%s waiting to collect tshirt. \n" COL_RESET, people[id].name);
       sem_wait(&tshirtQueue);
       printf(COL_DARK_MAGENTA "%s is collecting tshirt. \n" COL_RESET, people[id].name);
       people[id].status = COLLECTING_TSHIRT;
       sleep(2);
       sem_post(&tshirtQueue);
       people[id].status = EXITED;
   }

//   if(people[id].status == WAITING_TO_PERFORM) {
//        pthread_t acousticThread, electricThread;
//        pthread_create(&acousticThread,NULL, acousticLive, &(people[id].id));
//        pthread_create(&electricThread,NULL, electricLive, &(people[id].id));
//
//        pthread_join(&acousticThread, NULL);
//        pthread_join(&electricThread, NULL);
//   }
    return NULL;
}
