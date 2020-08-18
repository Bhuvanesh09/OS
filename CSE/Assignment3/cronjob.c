#include "header.h"

void cronjob(char **c)
{
	if(size1<7)
	{
		printf("Invalid Command\n");
		return ;
	}
	int arr[3];
	arr[0]=arr[1]=arr[2]=-1;
	for(int i=0;i<size1;i++)
	{
		if(strcmp(c[i],"-c")==0)
		{
			arr[0]=i;
		}
		if(strcmp(c[i],"-t")==0)
		{
			arr[1]=i;
		}
		if(strcmp(c[i],"-p")==0)
		{
			arr[2]=i;
		}
	}
	if(arr[0]==-1 || arr[1]==-1 || arr[2]==-1)
	{
		printf("Invalid Command\n");
		return ;
	}
	if(!(arr[0]==1 && arr[1]-arr[0]>0 && arr[2]-arr[1]==2 && arr[2]==size1-2))
	{
		printf("Invalid Command\n");
		return ;
	}
	pid_t pid;
	if((pid=fork())<0)
	{
		printf("ERROR: forking of child process failed\n");
		return ;
	}
	if(pid==0)
	{
		setpgid(0,0);
		char* comm[100];
		for(int i=arr[0]+1;i<arr[1];i++)
		{
			comm[i-arr[0]-1]=c[i];
			if(i==arr[1]-1)
			{
				comm[i-arr[0]]=NULL;
			}
		}
		long long int currtime,initime=time(0),prev=initime,diff=atoi(c[arr[2]-1]);
		while(time(0)<=initime+atoi(c[arr[2]+1]))
		{
			currtime=time(0);
			if(prev!=currtime && (currtime-initime)%diff==0 && currtime<=initime+atoi(c[arr[2]+1]))
			{
				prev=currtime;
				pid_t pid2;
				int status2;
				if((pid2=fork())<0)
				{
					printf("ERROR: forking of child process failed\n");
					break;
				}
				if(pid2==0)
				{
					setpgid(0,0);
					if(execvp(*comm,comm)<0)
					{
						printf("Invalid Command\n");
						exit(0);
					}
					exit(0);
				}
				else
				{
					waitpid(pid2,&status2,WUNTRACED);
					printf("\033[1;31m<\033[0m\033[1;32m%s\033[0m\033[1;33m@\033[0m\033[1;32m%s\033[0m:\033[1;34m%s\033[0m\033[1;31m>\033[0m\n",user,hostname,path2);
				}
			}
		}
		exit(0);
	}
	else
	{
		jobs[jobsize].pid=pid;
		jobs[jobsize].jobid=jobsize+1;
		jobs[jobsize].status=1;
		strcpy(jobs[jobsize].com,c[0]);
		jobsize++;
		printf("Job %s sent to background\nJobid = %d , pid = %d\n",c[0],jobsize,pid);
        signal(SIGCHLD,checkbg);
	}
}