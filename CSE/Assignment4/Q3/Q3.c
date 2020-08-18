#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct rider_details
{
	int id,cid;
};

int R,D,S,driver_status[100],server_status[100];

pthread_t rider_t[100];

pthread_mutex_t driver_m[100],server_m[100];

sem_t driver_s[100],free_cabs,free_servers;

int BookCab(int cabType,int maxWaitTime,int RideTime)
{
	struct timespec *wait=malloc(sizeof(struct timespec));
	wait->tv_sec=maxWaitTime;
	wait->tv_nsec=0;
	int x=sem_timedwait(&free_cabs,wait);
	if(x!=0)
	{
		return 0;
	}
    for(int i=0;i<D;i++)
    {
    	if(cabType)
    	{
    		if(driver_status[i]==0 || driver_status[i]==2)
    		{
    			sem_wait(&driver_s[i]);
	    		if(!(driver_status[i]==0 || driver_status[i]==2))
	    		{
	    			sem_post(&driver_s[i]); 
				    continue;
	    		}
	    		return i+1;
    		}
    	}
		else
		{
			if(driver_status[i]==0)
			{
    			sem_wait(&driver_s[i]); 
    			if(driver_status[i])
    			{
				    sem_post(&driver_s[i]); 
				    continue;
    			}
    			return i+1; 
			}
		}
    }
    if(cabType==0)
    {
    	return -1;
    }
	return 0;
}

void *MakePayment(void *arg)
{
	struct rider_details *args=arg;
    sem_wait(&free_servers);
    for(int i=0;i<S;i++,i%=S)
    {
    	if(server_status[i]==0)
    	{
    		pthread_mutex_lock(&server_m[i]);
    		if(server_status[i])
    		{
	    		pthread_mutex_unlock(&server_m[i]);
	    		continue;
    		}
    		server_status[i]=1;
    		printf("Payment in process by rider %d to cab %d through server %d has been initiated\n",args->id+1,args->cid,i+1);
    		sleep(2);
    		printf("Payment done by rider %d to cab %d through server %d\n",args->id+1,args->cid,i+1);
	   		pthread_mutex_unlock(&server_m[i]);
    		server_status[i]=0;
	   		break;
    	}
    }
    sem_post(&free_servers);
	return NULL;
}

void *rider_thread(void *arg)
{
	int tm=1+rand()%6;
	sleep(tm);
	struct rider_details *args=arg;
	printf("Rider %d online after %d seconds from the start\n",args->id+1,tm);
	int cabType=rand()%2;
	int maxWaitTime=1+rand()%6;
	int RideTime=1+rand()%5;
	if(cabType)
	{
		printf("Rider %d is looking for Pool Ride\n",args->id+1);
	}
	else
	{
		printf("Rider %d is looking for Premier Ride\n",args->id+1);
	}
	int boooking_status=BookCab(cabType,maxWaitTime,RideTime);
	if(boooking_status>0)
	{
		printf("Rider %d booked cab %d successfully and ride has started\n",args->id+1,boooking_status);
		if(cabType)
		{
			pthread_mutex_lock(&driver_m[boooking_status-1]);
			if(driver_status[boooking_status-1]==0)
			{
				driver_status[boooking_status-1]=2;
	  	 		sem_post(&free_cabs); 
				pthread_mutex_unlock(&driver_m[boooking_status-1]);
				sleep(RideTime);
				printf("Rider %d done with ride in cab %d in %d seconds\n",args->id+1,boooking_status,RideTime);
			}
			else
			{
				driver_status[boooking_status-1]=3;
				pthread_mutex_unlock(&driver_m[boooking_status-1]);
				sleep(RideTime);
				printf("Rider %d done with ride in cab %d in %d seconds\n",args->id+1,boooking_status,RideTime);
			}
			pthread_mutex_lock(&driver_m[boooking_status-1]);
			if(driver_status[boooking_status-1]==3)
			{
				driver_status[boooking_status-1]=2;
		  	 	sem_post(&free_cabs); 
			}
			else
			{
				driver_status[boooking_status-1]=0;
			}
			pthread_mutex_unlock(&driver_m[boooking_status-1]);
		}
		else
		{
			driver_status[boooking_status-1]=1;
			sleep(RideTime);
			printf("Rider %d done with ride in cab %d in %d seconds\n",args->id+1,boooking_status,RideTime);
			driver_status[boooking_status-1]=0;
	  	 	sem_post(&free_cabs); 
		}
		sem_post(&driver_s[boooking_status-1]);
		args->cid=boooking_status;
		MakePayment(arg);
	}
	else
	{
		printf("Rider %d couldn't book a ride due to wait timeout\n",args->id+1);
		if(boooking_status==-1)
		{
			sem_post(&free_cabs);
		}
	}
	return NULL;
}

void runsimulation()
{
	srand(time(0));
	sem_init(&free_cabs,0,D);
	sem_init(&free_servers,0,S);
	for(int i=0;i<D;i++)
	{
		pthread_mutex_init(&driver_m[i],NULL);
		sem_init(&driver_s[i],0,2); 
	}
	for(int i=0;i<S;i++)
	{
		pthread_mutex_init(&server_m[i],NULL);
	}
	for(int i=0;i<R;i++)
	{
		struct rider_details *p=malloc(sizeof(struct rider_details));
		p->id=i;
		pthread_create(&rider_t[i],NULL,rider_thread,p); 
	}
	for(int i=0;i<R;i++)
	{
		pthread_join(rider_t[i],NULL); 
	}
	printf("Simulation Ended\n");
	sem_destroy(&free_cabs);
	sem_destroy(&free_servers);
	for(int i=0;i<D;i++)
	{
		pthread_mutex_destroy(&driver_m[i]);
		sem_destroy(&driver_s[i]); 
	}
	for(int i=0;i<S;i++)
	{
		pthread_mutex_destroy(&server_m[i]);
	}
}

int main(void)
{
	printf("Enter the Number of riders,Number of drivers and Number of servers\n");
	scanf("%d %d %d",&R,&D,&S);
	runsimulation();
	return 0;
}