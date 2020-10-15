//
// Created by simpl on 15-10-2020.
//

#include "zone.h"
int performTest(int companyId,int zoneId, int studId){
    float prob = pharmaArray[companyId]->probSuccess;

    int result;
    result = (float) random()/ (float) RAND_MAX < prob ? 1 : 0;

    printf(COL_RED "Student %d on " COL_BLUE "Vaccination Zone %d " COL_RED "has been vaccinated which has success probability %f\n" COL_RESET,studId, zoneId, prob);

    if(result == 1){
        studentArray[studId]->progressState = ADMITTED;
        printf(COL_RED "Student %d has tested positive for antibodies. :) \n" COL_RESET, studId);
        printf(COL_RED "Student %d has been ADMITTED to the College. \n" COL_RESET, studId);
        studentsLeft -= 1 ;
    }
    else {

        studentArray[studId]->numTries += 1;
        printf(COL_RED "Student %d has tested negative for antibodies. (ROUND : %d) :( \n" COL_RESET, studId, studentArray[studId]->numTries);
        if(studentArray[studId]->numTries >= 3){
            studentArray[studId]->progressState = FAILED;
            printf(COL_RED "Student %d has been sent back to his home. \n" COL_RESET, studId);
            studentsLeft -= 1 ;
        }
        else {
            studentArray[studId]->progressState = CANDIDATE;
            printf(COL_RED "Student %d is waiting to be allocated a slot on a Vaccination Zone\n" COL_RESET, studId);
        }
    }

    return 0;
}
void * zoneLive(void * input){
    int zoneId = *(int *) input;
    while(studentsLeft > 0){
        delay(3);
        pthread_mutex_lock(&zoneMutexes[zoneId]);
        pthread_mutex_lock(&totalStuds);
//        printf(COL_CYAN "zone live %d enter\n" COL_RESET, zoneId);

        if(zonesArray[zoneId]->numSlots - zonesArray[zoneId]->occupiedSlots == 0 && zonesArray[zoneId]->numSlots != 0){

            printf(COL_BLUE "Vaccination Zone %d entering Vaccination Phase\n" COL_RESET, zoneId);
            for( int i=0; i<zonesArray[zoneId]->numSlots ; i++){
                performTest(zonesArray[zoneId]->companyId, zoneId,  zonesArray[zoneId]->studentIds[i]);
            }

            //reinit the slots for next phase of vaccination.
            zonesArray[zoneId]->numSlots = 0;
            zonesArray[zoneId]->occupiedSlots = 0;
        }
        else if(zonesArray[zoneId] -> numSlots == 0 && zonesArray[zoneId]->vaccinesLeft != 0){
            // we can call another group of studs for vaccination. :)
            printf("Students left : %d\n", studentsLeft);
            zonesArray[zoneId]->numSlots = min(8, min(studentsLeft, zonesArray[zoneId]->vaccinesLeft));
            zonesArray[zoneId]->vaccinesLeft -= zonesArray[zoneId]->numSlots;
           zonesArray[zoneId]->studentIds = (int *) malloc(sizeof(int) * zonesArray[zoneId]->numSlots);
            zonesArray[zoneId]->occupiedSlots = 0;
            printf(COL_BLUE "Vaccination zone %d is ready to vaccinate having %d slots :)\n" COL_RESET, zoneId, zonesArray[zoneId]->numSlots);
            if(zonesArray[zoneId]-> vaccinesLeft == 0){
                printf(COL_BLUE "Vaccination zone %d has ran out of vaccines for the next phase.\n" COL_RESET, zoneId);
            }
        } else if (zonesArray[zoneId]->vaccinesLeft == 0) {
            zonesArray[zoneId]->companyId = -1;
        }

//        printf(COL_CYAN "zone live %d exit\n" COL_RESET, zoneId);
        pthread_mutex_unlock(&totalStuds);
        pthread_mutex_unlock(&zoneMutexes[zoneId]);
    }
}
