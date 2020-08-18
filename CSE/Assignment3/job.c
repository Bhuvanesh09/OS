#include "header.h"

void job()
{
	char c1[100],c2[100],name[100];
	for(int i=0;i<jobsize;i++)
	{
		if(jobs[i].status==0)
		{
			continue;
		}
		sprintf(name,"/proc/%d/stat",jobs[i].pid);
		FILE *p=fopen(name,"r");
		if(p==NULL)
		{
			jobs[i].status=0;
			continue;
		}
		fscanf(p,"%s %s %s",c1,c1,c2);
		if(strcmp(c2,"T")==0)
		{
			printf("[%d] Stopped %s [%d]\n",jobs[i].jobid,c1,jobs[i].pid);
		}
		else
		{
			printf("[%d] Running %s [%d]\n",jobs[i].jobid,c1,jobs[i].pid);
		}
	}
}

void kjob(char **c)
{
	if(size1!=3)
	{
		printf("Invalid input\n");
		return ;
	}
	int i,f=1;
	for(i=0;i<jobsize;i++)
	{
		if(jobs[i].jobid==atoi(c[1]))
		{
			f=0;
			break;
		}
	}
	if(f)
	{
		printf("Job with jobid %s doesn't exist\n",c[1]);
		return ;
	}
	if(kill(jobs[i].pid,atoi(c[2]))<0)
	{
		perror("kill");
	}
}

void ovkill(int f)
{
	for(int i=0;i<jobsize;i++)
	{
		if(kill(jobs[i].pid,9)>=0);
		{
			if(f)
			{
				printf("Job with jobid = %d , pid = %d killed\n",jobs[i].jobid,jobs[i].pid);
			}
		}
		jobs[i].status=0;
	}
	if(f)
	{
		printf("All jobs killed\n");
	}
	jobsize=0;
}