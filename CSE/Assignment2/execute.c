#include"header.h"

void execothers(char **c,int bg)
{
	pid_t pid;
	int status;
	c[size1-bg]='\0';
	if((pid=fork())<0)
	{
		printf("ERROR: forking of child process failed\n");
		return ;
	}
	if(pid==0)
	{
		if(execvp(*c,c)<0)
		{
			perror("ERROR");
			return ;
		}
		exit(0);
	}
	else
	{
		if(bg)
		{
			jobs[jobsize].pid=pid;
			jobs[jobsize].status=1;
			strcpy(jobs[jobsize].com,c[0]);
			jobsize++;
			strcpy(c[0],"");
		}
		else
		{
			while(wait(&status)!=pid);
		}
	}
	strcpy(c[0],"");
}

int executecommand(char** c,char *path,char *path2,char *home)
{
	int numofcoms=9;
	char* commandslist[numofcoms];
	commandslist[0]="cd";
	commandslist[1]="pwd";
	commandslist[2]="echo";
	commandslist[3]="ls";
	commandslist[4]="clear";
	commandslist[5]="pinfo";
	commandslist[6]="history";
	commandslist[7]="watch";
	commandslist[8]="exit";
	int i;
	for(i=0;i<numofcoms;i++)
	{
		if(strcmp(commandslist[i],c[0])==0)
		{
			break;
		}
	}
	if(c[size1-1][0]=='&' && strlen(c[size1-1])==1)
	{
		i=numofcoms;
	}
	int l,a,f;
	switch(i)
	{
		case 0:
				if(strcmp(c[1],"")==0 || strcmp(c[1],".")==0)
				{
					return 1;
				}
				if(strcmp(c[1],"~")==0)
				{
					strcpy(c[1],home);
				}
				int f=chdir(c[1]);
				if(f<0)
				{
					perror(c[1]);
				}
				return 1;
		case 1:
				printf("%s\n",path2);
				return 1;
		case 2:
				echox(c);
				return 1;
		case 3:
				l=a=0;
				for(int i=1;i<size1;i++)
				{
					if(strcmp(c[i],"-l")==0)
					{
						l=1;
						c[i]="";
					}
					if(strcmp(c[i],"-a")==0)
					{
						a=1;
						c[i]="";
					}
					if(strcmp(c[i],"-la")==0 || strcmp(c[i],"-al")==0)
					{
						l=a=1;
						c[i]="";
					}
				}
				f=0;
				for(int i=1;i<size1;i++)
				{
					if(strcmp(c[i],"")!=0)
					{
						f=i;
						break;
					}
				}
				if(f)
				{
					if(strcmp(c[f],"~")==0)
					{
						strcpy(c[f],home);
					}
				}
				if(l && a)
				{
					if(f)
					{
						lsl(c[f],0);
					}
					else
					{
						lsl(path,0);
					}
					return 1;
				}
				if(a)
				{
					if(f)
					{
						printdir(c[f],0);
					}
					else
					{
						printdir(path,0);
					}
					return 1;
				}
				if(l)
				{
					if(f)
					{
						lsl(c[f],1);
					}
					else
					{
						lsl(path,1);
					}
					return 1;
				}
				if(f)
				{
					printdir(c[f],1);
				}
				else
				{
					printdir(path,1);
				}
				return 1;
		case 4:
				printf("\e[1;1H\e[2J");
				return 1;
		case 5:
				pinfo(c,home);
				return 1;
		case 6:
				historyexe(c);
				return 1;
		case 7:
				dirty(c);
				return 1;
		case 8:
				printf("\033[1;33mhasta la vista!\n\033[0m");
				exit(0);
		default:
				execothers(c,c[size1-1][0]=='&' && strlen(c[size1-1])==1);
				return 1;
	}
	return 1;
}