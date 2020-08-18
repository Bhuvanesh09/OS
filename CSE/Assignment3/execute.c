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
		setpgid(0,0);
		if(execvp(*c,c)<0)
		{
			printf("Invalid Command\n");
			exit(0);
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
		if(bg)
		{
			printf("Job %s sent to background\nJobid = %d , pid = %d\n",c[0],jobsize,pid);
            signal(SIGCHLD,checkbg);
		}
		else
		{
			tcsetpgrp(0,pid);
			waitpid(pid,&status,WUNTRACED);
			signal(SIGTTOU,SIG_IGN);
			tcsetpgrp(0,getpid());
			signal(SIGTTOU,SIG_DFL);
		}
	}
}

int executecommand(char **c,char *path,char *path2,char *home)
{
	if(size1==0)
	{
		return 1;
	}
	if(itsredirection(c))
	{
		redirection(c);
		return 1;
	}
	int numofcoms=17;
	char* commandslist[numofcoms];
	commandslist[0]="cd";
	commandslist[1]="pwd";
	commandslist[2]="echo";
	commandslist[3]="ls";
	commandslist[4]="clear";
	commandslist[5]="pinfo";
	commandslist[6]="history";
	commandslist[7]="watch";
	commandslist[8]="setenv";
	commandslist[9]="unsetenv";
	commandslist[10]="fg";
	commandslist[11]="bg";
	commandslist[12]="overkill";
	commandslist[13]="kjob";
	commandslist[14]="jobs";
	commandslist[15]="cronjob";
	commandslist[16]="quit";
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
				setenvv(c);
				return 1;
		case 9:
				unsetenvv(c);
				return 1;
		case 10:
				execute_fg(c);
				return 1;
		case 11:
				execute_bg(c);
				return 1;
		case 12:
				ovkill(1);
				return 1;
		case 13:
				kjob(c);
				return 1;
		case 14:
				job();
				return 1;
		case 15:
				cronjob(c);
				return 1;
		case 16:
				ovkill(0);
				printf("\033[1;33mhasta la vista!\n\033[0m");
				exit(0);
		default:
				execothers(c,c[size1-1][0]=='&' && strlen(c[size1-1])==1);
				return 1;
	}
	return 1;
}