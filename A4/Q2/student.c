//
// Created by simpl on 15-10-2020.
//

#include "student.h"
int tryForSlot(int studId){
    for(int i=0 ; i < num_zones; i++){
        int success = 0;
        pthread_mutex_lock(&zoneMutexes[i]);
        int availSlots = zonesArray[i]->numSlots - zonesArray[i]->occupiedSlots;
        if(availSlots > 0){
            zonesArray[i]->studentIds[zonesArray[i]->occupiedSlots] = studId;
            printf(COL_RED "Student %d has been assigned a slot on the " COL_BLUE "zone %d" COL_RED " and is waiting to be vaccinated. :)" COL_RESET, studId, i);
            success = 1;
            studentArray[studId]->progressState = WAITING;

            zonesArray[i]->occupiedSlots += 1;
        }

        pthread_mutex_unlock(&zoneMutexes[i]);

        if(success){
            return 1;
        }
    }

    return 0;
}
void *studentLife(void * input){
    int studId = *((int *) input);
    int timeArrival = randomCustom(1, 10);
    sleep(timeArrival);
    printf(COL_RED "Student %d has arrived at the gate.\n" COL_RESET, studId);

    while(studentArray[studId]->progressState == CANDIDATE || studentArray[studId]->progressState == WAITING){
        printf(COL_RED "Student %d is waiting to be allot a slot in any of the vaccination zones." COL_RESET, studId);
        if (studentArray[studId]->progressState == CANDIDATE) tryForSlot(studId);
    }
}