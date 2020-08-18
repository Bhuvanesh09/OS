#include "header.h"

int isup(char **c)
{
	if(size1!=1)
	{
		return 0;
	}
	char tmp[50]="\0",cc;
	for(int i=0;i<10;i++)
	{
		tmp[i*3]=27;
		tmp[i*3+1]=91;
		tmp[i*3+2]=65;
		tmp[(i+1)*3]='\0';
		if(strcmp(tmp,c[0])==0)
		{
			return i+1;
		}
	}
	return 0;
}

void uparrowk(char *user,char *hostname,int k,char *path2,char *lel)
{
	if(histsize<k)
	{
		printf("Command number %d not found in history\n",k);
		return ;
	}
	FILE *fd=fopen(historypath,"r");
	fseek(fd,0,SEEK_SET);
	char buf[10000],waste;
	for(int i=0;i<=histsize;i++)
	{
		fscanf(fd,"%[^\n]s",buf);
		fscanf(fd,"%c",&waste);
		if(i!=0)
		{
			strcpy(hist[i-1],buf);
		}
	}
	fclose(fd);
	printterm(user,hostname,path2);
	strcpy(lel,hist[histsize-k-1]);
	printf("%s\n",lel);
	histsize--;
	addtohistory(lel);
}