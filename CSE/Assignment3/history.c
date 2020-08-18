#include"header.h"

char historypath[10000];

void inithistory(char *hom)
{
	char buf[10000];
	strcpy(historypath,hom);
	strcat(historypath,"/history");
	FILE *fd=fopen(historypath,"r");
	if(fd==NULL)
	{
		fd=fopen(historypath,"w");
		fprintf(fd,"0\n");
	}
	else
	{
		fseek(fd,0,SEEK_END);
		if(ftell(fd)==0)
		{
			fd=fopen(historypath,"w");
			fprintf(fd,"0\n");
		}
	}
	fseek(fd,0,SEEK_SET);
	fscanf(fd,"%d",&histsize);
	fclose(fd);
}

void addtohistory(char *c)
{
	FILE *fd=fopen(historypath,"r");
	if(fd==NULL)
	{
		perror(historypath);
		exit(0);
	}
	char waste,buf[10000];
	fseek(fd,0,SEEK_SET);
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
	if(histsize==20)
	{
		for(int i=0;i<19;i++)
		{
			strcpy(hist[i],hist[i+1]);
		}
		histsize--;
	}
	strcpy(hist[histsize++],c);
	fd=fopen(historypath,"w+");
	if(fd==NULL)
	{
		perror(historypath);
		exit(0);
	}
	fseek(fd,0,SEEK_SET);
	fprintf(fd,"%d\n",histsize);
	for(int i=0;i<histsize;i++)
	{
		fprintf(fd,"%s\n",hist[i]);
	}
	fclose(fd);
}

void historyexe(char **c)
{
	int num=10;
	if(size1>1)
	{
		num=atoi(c[1]);
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
	for(int i=(0>histsize-num? 0:histsize-num);i<histsize;i++)
	{
		printf(" %d %s\n",i+1,hist[i]);
	}
}