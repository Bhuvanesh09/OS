#include <stdio.h>
#include "main.h"
void *shareMem(size_t size) {
    key_t mem_key = IPC_PRIVATE;
    // get shared memory of this much size and with this private key
    // what is 0666?
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);
    // attach the address space of shared memory to myself (callee)
    return (void *)shmat(shm_id, NULL, 0);
}
int main() {
    srand(time(0));

    printf("Kindly enter number of companies, zones, and students.\n");
    scanf("%d %d %d", &num_companies, &num_zones, &num_students);

    studentArray = (struct student **) shareMem(sizeof(struct student *) * num_students);
    zonesArray = (struct zone **) shareMem(sizeof(struct zone *) * num_zones);
    pharmaArray = (struct zone **) shareMem(sizeof(struct zone *) * num_companies);

    zoneMutexes = (pthread_mutex_t *) shareMem(sizeof(pthread_mutex_t) * num_zones);

    pthread_t *studentThreads = (pthread_t *) shareMem(sizeof(pthread_t) * num_students);
    pthread_t *zoneThreads = (pthread_t *) shareMem(sizeof(pthread_t) * num_zones);
    pthread_t *pharmaThreads = (pthread_t *) shareMem(sizeof(pthread_t) * num_companies);

    for(int i=0; i < num_zones; i++){
        zonesArray[i] = (struct zone *) shareMem(sizeof(struct zone));
        zonesArray[i] -> id = i;

        pthread_mutex_init(&zoneMutexes[i], NULL);
    }

    for(int i=0; i < num_students; i++){
        studentArray[i] = (struct student *) shareMem(sizeof(struct student));
        studentArray[i]->id = i;

    }
    for(int i=0; i < num_companies; i++){
        pharmaArray[i] = (struct pharma *) shareMem(sizeof(struct pharma));
        pharmaArray[i]->id = i ;

    }
    return 0;
}