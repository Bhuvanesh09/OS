#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>
#define _POSIX_C_SOURCE 199309L //required for clock
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <inttypes.h>
#include <math.h>
int *shareMem(size_t size) {
    key_t mem_key = IPC_PRIVATE;
    // get shared memory of this much size and with this private key
    // what is 0666?
    int shm_id = shmget(mem_key, size, IPC_CREAT | 0666);

    // attach the address space of shared memory to myself (callee)
    return (int *)shmat(shm_id, NULL, 0);
}
void swapCust(int *a, int *b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
    return;
}
void selectionSort(int *arr, int left, int right){
    int minIdx;
    for(int i=left; i < right; i++){
       minIdx = i;
       for(int j=i; j < right ; j++){
           minIdx = arr[minIdx] < arr[j] ? minIdx : j;
       }
       if(minIdx != i) swapCust(&arr[minIdx], &arr[i]);
    }

    return;
}

void printar(int *arr, int left, int right){
    for(int i=left; i<right; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void merge(int * arr, int left, int right){
//    printf("Entered: ");
//    printar(arr, left, right);
    int middle = (left + right)/2;
    int *sortedArr = (int *) malloc(sizeof(int) * (right - left +10 ));
    int i = left, leftTrack, rightTrack;

    for(leftTrack=0, rightTrack=middle; leftTrack != middle && rightTrack != right ; i++){
       if(arr[leftTrack] <= arr[rightTrack]) {
           sortedArr[i] = arr[leftTrack];
           leftTrack++;
       }else {
           sortedArr[i] = arr[rightTrack];
           rightTrack++;
       }
    }

    for(;leftTrack < middle;leftTrack++,i++){
        sortedArr[i] = arr[leftTrack];
    }
    for(;rightTrack < right;rightTrack++,i++){
        sortedArr[i] = arr[rightTrack];
    }
    for(int i=0, j=left; j<right; i++, j++){
//        printf("%d ", sortedArr[i]);
        arr[j] = sortedArr[i];
    }
//    printf("merged ^ \n");

    return;
}
void mergesort(int *arr, int left , int right){
    if(left == right) return;

    if(right - left <= 5) {
        selectionSort(arr, left, right);
        return;
    }

    int middle = (left + right) / 2;
    mergesort(arr, left, middle);
    mergesort(arr, middle, right);

    merge(arr, left, right);
    return;

}
void mergesort_parallel(int *arr, int left, int right){
    if(left == right) return;

    if(right - left <= 5) {
        selectionSort(arr, left, right);
//        printf("Did Selection sort from %d to %d \n", left, right);
        for(int i=left; i<right; i++) {
//            printf("%d ", arr[i]);
        }
//        printf("\n");
//        fflush(stdout);
        return;
    }
    int middle = (left + right)/2;

    int pid_left = fork(), pid_right;

    if(pid_left == 0){
        mergesort_parallel(arr, left, middle);
        exit(0);
    }
    else {
        pid_right = fork();
        if(pid_right == 0){
            mergesort_parallel(arr, middle, right);
            exit(0);
        }
        else {
            int status;
            waitpid(pid_left, &status, 0);
            waitpid(pid_right, &status, 0);
        }
    }

    merge(arr, left, right);
    return;

}
void runSorts(long long int n){

    struct timespec ts;

    //getting shared memory
    int *arr = shareMem(sizeof(int)*(n+1));
    for(int i=0;i<n;i++) scanf("%d", arr+i);

    int brr[n+1];
    for(int i=0;i<n;i++) brr[i] = arr[i];

    printf("Running concurrent_quicksort for n = %lld\n", n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    long double st = ts.tv_nsec/(1e9)+ts.tv_sec;

    //multiprocess mergesort
    mergesort_parallel(arr, 0, n);
    for(int i=0; i<n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    long double en = ts.tv_nsec/(1e9)+ts.tv_sec;
    printf("time = %Lf\n", en - st);
    long double t1 = en-st;

//    pthread_t tid;
//    struct arg a;
//    a.l = 0;
//    a.r = n-1;
//    a.arr = brr;
//    printf("Running threaded_concurrent_quicksort for n = %lld\n", n);
//    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
//    st = ts.tv_nsec/(1e9)+ts.tv_sec;

//    //multithreaded mergesort
//    pthread_create(&tid, NULL, threaded_quickSort, &a);
//    pthread_join(tid, NULL);
//    for(int i=0; i<n; i++){
//        printf("%d ",a.arr[i]);
//    }
//    printf("\n");
//    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
//    en = ts.tv_nsec/(1e9)+ts.tv_sec;
//    printf("time = %Lf\n", en - st);
//    long double t2 = en-st;

    printf("Running normal_quicksort for n = %lld\n", n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    st = ts.tv_nsec/(1e9)+ts.tv_sec;

    // normal mergesort
    mergesort(brr, 0, n);
    for(int i=0; i<n; i++){
        printf("%d ",brr[i]);
    }
    printf("\n");
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    en = ts.tv_nsec/(1e9)+ts.tv_sec;
    printf("time = %Lf\n", en - st);
    long double t3 = en - st;

    printf("normal_quicksort ran:\n\t[ %Lf ] times faster than concurrent_quicksort\n\t times faster than threaded_concurrent_quicksort\n\n\n", t1/t3  );
    shmdt(arr);
    return;
}
int main() {
    long long int n;
    scanf("%lld", &n);
    runSorts(n);
    return 0;
}
