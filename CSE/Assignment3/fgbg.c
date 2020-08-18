#include "header.h"

void execute_fg(char **c)
{
	if(size1!=2)
	{
		printf("Invalid input\n");
		return ;
	}
	int f=0,i;
	pid_t p=atoi(c[1]);
	for(i=0;i<jobsize;i++)
	{
		if(jobs[i].jobid==p)
		{
			f=1;
			break;
		}
	}
	if(f)
	{
		int status;
		p=jobs[i].pid;
		kill(p,SIGCONT);
		tcsetpgrp(0,p);
		waitpid(p,&status,WUNTRACED);
		signal(SIGTTOU,SIG_IGN);
		tcsetpgrp(0,getpid());
		signal(SIGTTOU,SIG_DFL);
	}
	else
	{
		printf("Process with jobid %d doesn't exist\n",p);
	}
}

void execute_bg(char **c)
{
	if(size1!=2)
	{
		printf("Invalid input\n");
		return ;
	}
	int f=0,i;
	pid_t p=atoi(c[1]);
	for(i=0;i<jobsize;i++)
	{
		if(jobs[i].jobid==p)
		{
			f=1;
			break;
		}
	}
	if(f)
	{
		int status;
		printf("This process is running now\nName = %s\nJobid = %d\nPid = %d\n",jobs[i].com,p,jobs[i].pid);
		kill(jobs[i].pid,SIGCONT);
	}
	else
	{
		printf("Process with jobid %d doesn't exist\n",p);
	}
}