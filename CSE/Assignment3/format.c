#include"header.h"

void getcwdstr(char *arr)
{
	getcwd(arr,sizeof(char)*10000);
}

void gethome(char *from,char *to)
{
	from[strlen(from)-5]='\0';
	realpath(from,to);
}

char *getusername()
{
	return getenv("USER");
}

void gethname(char *arr)
{
	gethostname(arr,10000);
}

void printterm(char *usr,char *host,char *path)
{
	printf("\033[1;31m<\033[0m\033[1;32m%s\033[0m\033[1;33m@\033[0m\033[1;32m%s\033[0m:\033[1;34m%s\033[0m\033[1;31m>\033[0m ",usr,host,path);
}

int makerel(char *path,char *home,char *path2)
{
	if(strlen(path)<strlen(home))
	{
		strcpy(path2,path);
		return 0;
	}
	for(int i=0;i<strlen(home);i++)
	{
		if(path[i]!=home[i])
		{
			strcpy(path2,path);
			return 0;
		}
	}
	int i;
	for(i=strlen(home);i<strlen(path);i++)
	{
		path2[i-strlen(home)+1]=path[i];
	}
	path2[0]='~';
	path2[i-strlen(home)+1]='\0';
	return 1;
}