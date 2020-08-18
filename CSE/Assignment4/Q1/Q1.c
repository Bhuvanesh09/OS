#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

struct data
{
	int *arr,l,r,pivot;
};

int *shareMem(size_t size)
{
	key_t mem_key=IPC_PRIVATE;
	int shm_id=shmget(mem_key,size,IPC_CREAT | 0666);
	return (int*)shmat(shm_id,NULL,0);
}

int randompos(int l,int r)
{
	if(l>r)
	{
		return 0;
	}
	return l+rand()%(r-l+1);
}

void swap(int *a,int *b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}

void printarr(int *arr,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int partition(int *arr,int l,int r,int pivot)
{
	int i=l-1;
	swap(&arr[pivot],&arr[r]);
	pivot=arr[r];
	for(int j=l;j<r;j++)
	{
		if(arr[j]<=pivot)
		{
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	i++;
	swap(&arr[i],&arr[r]);
	return i;
}

void *quicksort_threads(void *arg)
{
	struct data *args=arg;
	int *arr=args->arr,l=args->l,r=args->r,pivot=args->pivot;
	if(l<r)
	{
		if(r-l<5)
		{
			for(int i=l+1;i<=r;i++)
			{
				for(int j=i-1;j>=l;j--)
				{
					if(arr[j]>arr[j+1])
					{
						swap(&arr[j],&arr[j+1]);
					}
					else
					{
						break;
					}
				}
			}
			return NULL;
		}
		int pos=partition(arr,l,r,pivot);
		struct data *args1=malloc(sizeof(struct data)),*args2=malloc(sizeof(struct data));
		pthread_t p1,p2;
		args1->arr=arr;
		args1->l=pos+1;
		args1->r=r;
		args1->pivot=randompos(pos+1,r);
		pthread_create(&p1,NULL,quicksort_threads,args1);
		args2->arr=arr;
		args2->l=l;
		args2->r=pos-1;
		args2->pivot=randompos(l,pos-1);
		pthread_create(&p2,NULL,quicksort_threads,args2);
		pthread_join(p1,NULL);
		pthread_join(p2,NULL);
	}
	return NULL;
}

void *quicksort_processes(void *arg)
{
	struct data *args=arg;
	int *arr=args->arr,l=args->l,r=args->r,pivot=args->pivot;
	if(l<r)
	{
		if(r-l<5)
		{
			for(int i=l+1;i<=r;i++)
			{
				for(int j=i-1;j>=l;j--)
				{
					if(arr[j]>arr[j+1])
					{
						swap(&arr[j],&arr[j+1]);
					}
					else
					{
						break;
					}
				}
			}
			return NULL;
		}
		int pos=partition(arr,l,r,pivot);
		struct data *args1=malloc(sizeof(struct data)),*args2=malloc(sizeof(struct data));
		args1->arr=arr;
		args1->l=pos+1;
		args1->r=r;
		args1->pivot=randompos(pos+1,r);
		args2->arr=arr;
		args2->l=l;
		args2->r=pos-1;
		args2->pivot=randompos(l,pos-1);
		int pid1=fork(),pid2;
		if(pid1<0)
		{
			printf("Forking Error\n");
			return NULL;
		}
		if(pid1==0)
		{
			quicksort_processes(args1);
			_exit(1);
		}
		else
		{
			pid2=fork();
			if(pid2<0)
			{
				printf("Forking Error\n");
				return NULL;
			}
			if(pid2==0)
			{
				quicksort_processes(args2);
				_exit(1);
			}
			else
			{
				int status;
				waitpid(pid1,&status,0);
				waitpid(pid2,&status,0);
			}
		}
	}
	return NULL;
}

void *quicksort_normal(void *arg)
{
	struct data *args=arg;
	int *arr=args->arr,l=args->l,r=args->r,pivot=args->pivot;
	if(l<r)
	{
		if(r-l<5)
		{
			for(int i=l+1;i<=r;i++)
			{
				for(int j=i-1;j>=l;j--)
				{
					if(arr[j]>arr[j+1])
					{
						swap(&arr[j],&arr[j+1]);
					}
					else
					{
						break;
					}
				}
			}
			return NULL;
		}
		int pos=partition(arr,l,r,pivot);
		struct data *args1=malloc(sizeof(struct data)),*args2=malloc(sizeof(struct data));
		args1->arr=arr;
		args1->l=pos+1;
		args1->r=r;
		args1->pivot=randompos(pos+1,r);
		quicksort_normal(args1);
		args2->arr=arr;
		args2->l=l;
		args2->r=pos-1;
		args2->pivot=randompos(l,pos-1);
		quicksort_normal(args2);
	}
	return NULL;
}

void runsorts()
{
	int n;
	scanf("%d",&n);
	int *arr=shareMem(sizeof(int)*(n+5));
	int crr[n+5];
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	pthread_t p1;
	int brr[n+5];
	for(int i=0;i<n;i++)
	{
		crr[i]=brr[i]=arr[i];
	}
	struct data *args=malloc(sizeof(struct data));
	args->arr=brr;
	args->l=0;
	args->r=n-1;
	args->pivot=randompos(0,n-1);
	struct timespec ts;
	printf("Running threaded_concurrent_quicksort\n");
	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	long double st=ts.tv_nsec/(1e9)+ts.tv_sec;

	pthread_create(&p1,NULL,quicksort_threads,args);
	pthread_join(p1,NULL);

	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	long double en=ts.tv_nsec/(1e9)+ts.tv_sec;
	// printarr(brr,n);
	printf("time = %Lf\n",en-st);

	args->arr=arr;
	printf("Running process_concurrent_quicksort\n");
	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	st=ts.tv_nsec/(1e9)+ts.tv_sec;

	quicksort_processes(args);

	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	en=ts.tv_nsec/(1e9)+ts.tv_sec;
	// printarr(arr,n);
	printf("time = %Lf\n",en-st);

	args->arr=crr;
	printf("Running normal_concurrent_quicksort\n");
	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	st=ts.tv_nsec/(1e9)+ts.tv_sec;

	quicksort_normal(args);

	clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
	en=ts.tv_nsec/(1e9)+ts.tv_sec;
	// printarr(crr,n);
	printf("time = %Lf\n",en-st);
}

int main(void)
{
	runsorts();
	return 0;
}