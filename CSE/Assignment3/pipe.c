#include"header.h"

int itspipe(char **c)
{
	int f=0,arr[10004];
	for(int i=0;i<size1;i++)
	{
		if(strcmp(c[i],"|")==0)
		{
			arr[f++]=i;
		}
	}
	if(f>0)
	{
		if(arr[0]==0 || arr[f-1]==size1-1)
		{
			return -1;
		}
	}
	for(int i=1;i<f;i++)
	{
		if(arr[i]-arr[i-1]==1)
		{
			return -1;
		}
	}
	return (f>0);
}

void piping(char *c,char *path,char *path2,char *home)
{
	char *comm[10000],*tok=strtok(c,"|");
	int pipenos=0,i;
	while(tok!=NULL)
	{
		comm[pipenos++]=tok;
		tok=strtok(NULL,"|");
	}
	int stdin=dup(0),stdou=dup(1),in1=dup(stdin),out1;
	for(i=0;i<pipenos-1;i++)
	{
		if(dup2(in1,0)!=0)
		{
			perror("dup2 Failed\n");
		}

		close(in1);

		int inter[2];
		if(pipe(inter)<0)
		{
			perror("Pipes Failed");
		}
		out1=inter[1];
		in1=inter[0];

		if(dup2(out1,1)!=1)
		{
			perror("dup2 Failed\n");
		}
		close(out1);
		char* tmp[100];
		makeinp(comm[i],tmp);
		executecommand(tmp,path,path2,home);
	}

	if(dup2(in1,0)!=0)
	{
		perror("dup2 Failed\n");
	}

	close(in1);

	out1=dup(stdou);

	if(dup2(out1,1)!=1)
	{
		perror("dup2 Failed\n");
	}
	close(out1);
	char* tmp[100];
	makeinp(comm[pipenos-1],tmp);
	executecommand(tmp,path,path2,home);

	dup2(stdin,0);
	dup2(stdou,1);
	return;
}