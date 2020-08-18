#include"header.h"

int pinfo(char **args,char *home)
{
	char *path="/proc/",newp[10000];
	if(args[1]==NULL)
	{
		sprintf(newp,"%s%d",path,getpid());
	}
	else
	{
		sprintf(newp,"%s%s",path,args[1]);
	}
	char stats[10000];
	sprintf(stats,"%s/stat",newp);
	FILE* f=fopen(stats ,"r");
	if(f==NULL)
	{
		perror("ERROR");
		return 0;
	}
	int pid;
	char stat,residue[30];
	fscanf(f,"%d",&pid);
	fscanf(f,"%s",residue);
	fscanf(f," %c",&stat);
	printf("Process Id --> %d\nProcess Status --> %c\n",pid,stat);
	fclose(f);
	char tarr[10000];
	sprintf(tarr,"%s/statm",newp);
	f=fopen(tarr,"r");
	if(f==NULL)
	{
		perror("ERROR");
		return 0;
	}
	int size;
	fscanf(f,"%d",&size);
	printf("memory --> %d {Virtual Memory}\n",size);
	fclose(f);
	sprintf(tarr,"%s/exe",newp);
	char tmparr[50]={0};
	int flag=0;
	if(readlink(tarr,tmparr,sizeof(tmparr))<0)
	{
		perror("readlink");
		return 0;
	}
	if(strlen(tmparr)<strlen(home))
	{
		printf("Executable Path --> %s\n",tmparr);
		return 1;
	}
	for(int i=0;i<strlen(home);i++)
	{
		if(home[i]!=tmparr[i])
		{
			flag=1;
			break;
		}
	}
	if(flag)
	{
		printf("Executable Path -- %s\n",tmparr);
	}
	else
	{
		printf("Executable Path -- ~%s\n",tmparr+strlen(home));
	}
	return 1;
}