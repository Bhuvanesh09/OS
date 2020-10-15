//
// Created by simpl on 15-10-2020.
//

#include "pharma.h"
int dispatchVaccines(int companyId){
    int flag = 0;
    for(int i=0; i<num_zones; i++){
        pthread_mutex_lock(&zoneMutexes[i]);
        if(zonesArray[i]->companyId == -1){
            zonesArray[i]->companyId = companyId;
            zonesArray[i]->vaccinesLeft = pharmaArray[companyId]->batchStrength;
            printf(COL_GREEN "Pharmaceutical Company %d is delivering a vaccine batch to Vaccination Zone %d which has success probability %f" COL_RESET, companyId, i, pharmaArray[companyId]->probSuccess);
            flag = 1;
            pharmaArray[companyId]->availBatches -= 1;
        }
        pthread_mutex_unlock(&zoneMutexes[i]);

        if(flag == 1) return 0;
    }
    return 0;
}
void * pharmaLive(void * input){
    int companyId = *(int *)  input;
    while(studentsLeft > 0){
        if(pharmaArray[companyId]->availBatches == 0){
            //No batches left so now I have to check if I need to produce more or not (by checking if all my vaccines are consumed)
            int flag = 1;
            for(int i=0; i < num_zones; i++){
                if(zonesArray[i]->companyId == companyId) flag = 0 ;
            }

            if(flag){
                printf(COL_GREEN "All the vaccines prepared by Pharmaceutical Company %d are emptied. Resuming production now." COL_RESET, companyId);
                printf(COL_GREEN "Pharmaceutical Company %d is preparing %d batches of vaccines which have success probability %f" COL_RESET, companyId, pharmaArray[companyId]->numBatchesProduced, pharmaArray[companyId]->probSuccess);
                sleep(pharmaArray[companyId]->productionTime);
                pharmaArray[companyId]->availBatches = pharmaArray[companyId]->numBatchesProduced;
                printf(COL_GREEN "Pharmaceutical Company %d has prepared %d batches of vaccines which have success probability %f. Waiting for all the vaccines to be used to resume production" COL_RESET, companyId, pharmaArray[companyId]->numBatchesProduced, pharmaArray[companyId]->probSuccess);
            }
        }
        else { // Num of batches are not 0 so we can send them still. :)
            dispatchVaccines(companyId);
        }
    }
}
