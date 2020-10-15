#include <stdio.h>
#include "main.h"
int min(int a, int b){
    return a < b ? a : b ;
}
void *shareMem(size_t size) {
    key_t mem_key = IPC_PRIVATE;
    // get shared memory of this much size and with this private key
    // what is 0666?
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);
    // attach the address space of shared memory to myself (callee)
    return (void *)shmat(shm_id, NULL, 0);
}
void delay(int time) {
    const clock_t start_time = clock();
    while (clock() - start_time < time * CLOCKS_PER_SEC);
}
int randomCustom(int l, int r) {
    return rand() % (r - l + 1) + l;
}
int main() {
    srand(time(0));

    printf("Kindly enter number of companies, zones, and students.\n");
    scanf("%d %d %d", &num_companies, &num_zones, &num_students);
    float *probs = (float *) shareMem(sizeof(float) * num_companies);

    for(int i=0; i<num_companies; i++){
        scanf("%f", &probs[i]);
    }
    studentsLeft = num_students;
    decoyLeft = num_students;
    studentArray = (struct student **) shareMem(sizeof(struct student *) * num_students);
    zonesArray = (struct zone **) shareMem(sizeof(struct zone *) * num_zones);
    pharmaArray = (struct pharma **) shareMem(sizeof(struct pharma *) * num_companies);

    zoneMutexes = (pthread_mutex_t *) shareMem(sizeof(pthread_mutex_t) * num_zones);

    pthread_t *studentThreads = (pthread_t *) shareMem(sizeof(pthread_t) * num_students);
    pthread_t *zoneThreads = (pthread_t *) shareMem(sizeof(pthread_t) * num_zones);
    pthread_t *pharmaThreads = (pthread_t *) shareMem(sizeof(pthread_t) * num_companies);

    for(int i=0; i < num_zones; i++){
        zonesArray[i] = (struct zone *) shareMem(sizeof(struct zone));
        zonesArray[i] -> id = i;
        pthread_mutex_init(&zoneMutexes[i], NULL);
    }
    pthread_mutex_init(&totalStuds, NULL);
    for(int i=0; i < num_students; i++){
        studentArray[i] = (struct student *) shareMem(sizeof(struct student));
        studentArray[i]->id = i;
        studentArray[i]->progressState = CANDIDATE;
        studentArray[i]->numTries = 0;
    }
    for(int i=0; i < num_companies; i++){
        pharmaArray[i] = (struct pharma *) shareMem(sizeof(struct pharma));
        pharmaArray[i]->id = i ;
        pharmaArray[i]->numBatchesProduced = randomCustom(1,5);
        pharmaArray[i]->batchStrength = randomCustom(10,20);
        pharmaArray[i]->probSuccess = probs[i];
        pharmaArray[i]->productionTime = randomCustom(2,5);
    }

    for(int i=0; i < num_students; i++){
        pthread_create(&studentThreads[i], NULL, studentLife, &(studentArray[i]->id));
    }
    for(int i=0; i < num_zones; i++){
        pthread_create(&zoneThreads[i], NULL, zoneLive, &(zonesArray[i]->id));
    }
    for(int i=0; i < num_companies; i++){
        pthread_create(&pharmaThreads[i], NULL, pharmaLive, &(pharmaArray[i]->id));
    }

    for(int i=0; i < num_students; i++){
        pthread_join(studentThreads[i], NULL);
    }

    printf("EXIT\n");

    return 0;
}