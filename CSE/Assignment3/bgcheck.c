#include"header.h"

void checkbg()
{
	pid_t pid;
	int status;
	while((pid=waitpid(-1,&status,WNOHANG | WUNTRACED))>0)
	{
		if(WIFEXITED(status))
		{
			for(int i=0;i<jobsize;++i)
			{
				if(jobs[i].pid==pid && jobs[i].status)
				{
					jobs[i].status=0;
					fprintf(stderr,"\nProcess %s with pid %d exited normally.\nPress [Enter]\n",jobs[i].com,pid);
					break;
				}
			}
		}
		if(WIFSIGNALED(status))
		{
			for(int i=0;i<jobsize;++i)
			{
				if(jobs[i].pid==pid && jobs[i].status)
				{
					jobs[i].status=0;
					fprintf(stderr,"\nProcess %s with pid %d terminated by a signal.\nPress [Enter]\n",jobs[i].com,pid);
					break;
				}
			}
		}
	}
	int pos=0;
	for(int i=0;i<jobsize;i++)
	{
		if(jobs[i].status)
		{
			jobs[pos++]=jobs[i];
		}
	}
	jobsize=pos;
}