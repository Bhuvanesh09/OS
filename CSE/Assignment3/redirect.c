#include "header.h"

int itsredirection(char **c)
{
	for(int i=1;i<size1-1;i++)
	{
		if(strcmp(c[i],">")==0 || strcmp(c[i],">>")==0 || strcmp(c[i],"<")==0)
		{
			return 1;
		}
	}
	return 0;
}

int redirection(char **c)
{
	int f1=0,f2=0,f3=0,inn,outt,fd[2],pos=100;
	char in[10000],out[10000];
	for(int i=0;i<size1;i++)
	{
		if(strcmp(c[i],"<")==0)
		{
			f1=i;
		}
		if(strcmp(c[i],">")==0)
		{
			f2=i;
		}
		if(strcmp(c[i],">>")==0)
		{
			f3=i;
		}
	}
	if(f1)
	{
		pos=f1;
		strcpy(in,c[f1+1]);
	}
	if(f2 || f3)
	{
		strcpy(out,c[f2+f3+1]);
		if(f2+f3<=pos)
		{
			pos=f2+f3;
		}
	}
	c[pos]=NULL;
	if(f1)
	{
		struct stat tmp;
		if(stat(in,&tmp)<0)
		{
			perror(in);
		}
		inn=dup(0);
   		fd[0]=open(in,O_RDONLY,0644);
		dup2(fd[0],0);
	}
	if(f2 || f3)
	{
		outt=dup(1);
		if(f2)
	    {
	    	fd[1]=open(out,O_WRONLY | O_CREAT | O_TRUNC,0644);
	    }
		else
		{
	    	fd[1]=open(out,O_WRONLY | O_CREAT | O_APPEND,0644);
		}
		if(dup2(fd[1],1)<0)
		{
			perror("dup2 failed");
			return 0;
		}
	}
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		close(fd[1]);
		perror("Fork error");
		return 0;
	}
	if(pid==0)
	{
		if(execvp(c[0],c)<0)
		{
			perror(c[0]);
			exit(0);
		}
	}
	else
	{
		wait(NULL);
		dup2(inn,0);
		dup2(outt,1);
	}
}