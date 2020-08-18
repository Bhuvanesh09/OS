#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

struct chef_details
{
	int id,r,p,status;
};

struct table_details
{
	int id,status,slot,present;
};

struct student_details
{
	int id;
};
int min(int a,int b)
{
	if(a<b)
	{
		return a;
	}
	return b;
}

int N,M,K,queue[100][100];

struct chef_details robot_status[100];

struct table_details table_status[100];

pthread_t student[100],table[100],robot[100];

pthread_mutex_t robot_m[100],table_m[100];

pthread_cond_t robot_c[100],table_c[100];

void *biryani_ready(void *arg)
{
	struct chef_details *args=arg;
	for(int i=0;i<args->r;i++)
	{
		pthread_mutex_lock(&robot_m[args->id]);
		robot_status[args->id].status=1;
		pthread_cond_wait(&robot_c[args->id],&robot_m[args->id]);
		pthread_mutex_unlock(&robot_m[args->id]);
	}
	return NULL;
}

void *robot_t(void *arg)
{
	struct chef_details *args=arg;
	while(1)
	{
		int w=2+rand()%4,r=1+rand()%10,p=25+rand()%26;
		printf("Robot %d preparing %d vessels of capacity %d in %d seconds\n",args->id+1,r,p,w);
		sleep(w);
		printf("Robot %d done preparing %d vessels of capacity %d in %d seconds\n",args->id+1,r,p,w);
		robot_status[args->id].r=args->r=r;
		robot_status[args->id].p=args->p=p;
		biryani_ready(arg);
	}
	return NULL;
}

void *ready_to_serve_table(int number_of_slots,int id)
{
	pthread_mutex_lock(&table_m[id]);
	queue[id][0]=0;
	printf("Table %d entered serving phase with %d slots\n",id+1,number_of_slots);
	table_status[id].status=1;
	pthread_cond_wait(&table_c[id],&table_m[id]);
	pthread_mutex_unlock(&table_m[id]);
	printf("Served %d slot(s) of biryani from table %d\n",number_of_slots,id+1);
	queue[id][0]=table_status[id].status=0;
	return NULL;
}

void *table_t(void *arg)
{
	struct table_details *args=arg;
	for(int i=0;i<M;i++,i%=M)
	{
		if(robot_status[i].status)
		{
			pthread_mutex_lock(&robot_m[i]);
			if(robot_status[i].status==0)
			{
				pthread_mutex_unlock(&robot_m[i]);
				continue;
			}
			robot_status[i].status=0;
			printf("Vessel of capacity %d given by chef with id %d to table %d\n",robot_status[i].p,i+1,args->id+1);
			pthread_cond_signal(&robot_c[i]);
			pthread_mutex_unlock(&robot_m[i]);
			sleep(0.5);
			table_status[args->id].slot=1+rand()%10;
			table_status[args->id].present=0;
			ready_to_serve_table(table_status[args->id].slot,args->id);
		}
	}
	return NULL;
}

int wait_for_slot(void *arg)
{
	struct student_details *args=arg;
	for(int i=0;;i++,i%=N)
	{
		if(table_status[i].status==1)
		{
			pthread_mutex_lock(&table_m[i]);
			if(table_status[i].status==0 || table_status[i].status==2 || table_status[i].present>=table_status[i].slot)
			{
				pthread_mutex_unlock(&table_m[i]);
				continue;
			}
			return i;
		}
	}
}

void student_in_slot(void *arg,int i)
{
	struct student_details *args=arg;
	table_status[i].present++;
	queue[i][0]++;
	queue[i][queue[i][0]]=args->id;
	if(table_status[i].present==table_status[i].slot)
	{
		table_status[i].status=2;
		pthread_cond_signal(&table_c[i]);
	}
	printf("Student with id %d served biryani from table %d\n",args->id+1,i+1);
	pthread_mutex_unlock(&table_m[i]);
}

void *student_t(void *arg)
{
	sleep(1+rand()%4);
	struct student_details *args=arg;
	printf("Student with id - %d has arrived in mess and is waiting for slot\n",args->id+1);
	int x=wait_for_slot(arg);
	student_in_slot(arg,x);
	return NULL;
}

void start_simulation()
{
	for(int i=0;i<N;i++)
	{
	    pthread_mutex_init(&table_m[i],NULL);
	    pthread_cond_init(&table_c[i],NULL);
	}
	for(int i=0;i<M;i++)
	{
	    pthread_mutex_init(&robot_m[i],NULL);
		pthread_cond_init(&robot_c[i],NULL);
	}
	srand(time(0));
	for(int i=0;i<M;i++)
	{
		struct chef_details *p=malloc(sizeof(struct chef_details));
		p->id=i;
		pthread_create(&robot[i],NULL,robot_t,p);
	}
	for(int i=0;i<N;i++)
	{
		struct table_details *p=malloc(sizeof(struct table_details));
		p->id=i;
		pthread_create(&table[i],NULL,table_t,p);
	}
	for(int i=0;i<K;i++)
	{
		struct student_details *p=malloc(sizeof(struct student_details));
		p->id=i;
		pthread_create(&student[i],NULL,student_t,p);
	}
	for(int i=0;i<K;i++)
	{
		pthread_join(student[i],NULL);
	}
	printf("All %d students served biryani successfully\nSimulation Over\n",K);
	for(int i=0;i<M;i++)
	{
	    pthread_mutex_destroy(&robot_m[i]);
	    pthread_cond_destroy(&robot_c[i]);
	}
	for(int i=0;i<N;i++)
	{
	    pthread_mutex_destroy(&table_m[i]);
	    pthread_cond_destroy(&table_c[i]);
	}
}

int main(void)
{
	printf("Enter the Number of tables,Number of robots and Number of students\n");
	scanf("%d %d %d",&N,&M,&K);
	start_simulation();
	exit(0);
}