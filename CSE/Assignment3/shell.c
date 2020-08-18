#include"header.h"

char hist[25][10000],tmp[10000],path[10000],hostname[10000],path2[10000];
char *user;
int size,size1,histsize,jobsize=0;
struct node jobs[10000];

int main(int argc,char* argv[])
{
	signal(SIGINT,handler1);
	signal(SIGTSTP,handler2);
	user=getusername();
	gethname(hostname);
	char home[10000];
	char* inp[100];
	char* inp1[100];
	gethome(argv[0],home);
	printf("\e[1;1H\e[2J");
	inithistory(home);
	while(1)
	{
		resetinp(inp1);
		getcwdstr(path);
		makerel(path,home,path2);
		printterm(user,hostname,path2);
		takeinp(inp1);
		checkbg();
		for(int i=0;i<size;i++)
		{
			strcpy(tmp,inp1[i]);
			makeinp(inp1[i],inp);
			int tt=isup(inp);
			if(tt)
			{
				uparrowk(user,hostname,tt,path2,inp1[i]);
				makeinp(inp1[i],inp);
			}
			tt=itspipe(inp);
			if(tt<0)
			{
				printf("Invalid Command\n");
				continue;
			}
			if(tt>0)
			{
				piping(tmp,path,path2,home);
				continue;
			}
			executecommand(inp,path,path2,home);
		}
	}
	return 0;
}