#include"header.h"

int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec=0;
    tv.tv_usec=0;
    FD_ZERO(&fds);
    FD_SET(0,&fds);
    select(1,&fds,NULL,NULL,&tv);
    return FD_ISSET(0,&fds);
}

void nonblock(int state)
{
	struct termios ttystate;
	tcgetattr(0,&ttystate);
	if (state==0)
	{
		ttystate.c_lflag&=~ICANON;
		ttystate.c_cc[VMIN]=1;
	}
	else
	{
		ttystate.c_lflag|=ICANON;
	}
	tcsetattr(0,TCSANOW,&ttystate);
}

void finddirtysize()
{
	FILE* f=fopen("/proc/meminfo","r");
	char buf[10000];
	for(int i=0;i<50;i++)
	{
		fscanf(f,"%s",buf);
	}
	printf("Dirty Mem : %s kB\n",buf);
}

void dirty(char **c)
{
	if(!(size1==2 || size1==4))
	{
		printf("watch : Invalid Syntax\n");
		return ;
	}
	int tim;
	if(size1==2 && strcmp(c[1],"dirty")==0)
	{
		tim=2;
	}
	else
	{
		if(size1==4 && strcmp(c[1],"-n")==0)
		{
			if(strcmp(c[3],"dirty")==0)
			{
				tim=atoi(c[2]);
			}
			else
			{
				printf("watch : Invalid Syntax\n");
				return ;
			}
		}
		else
		{
			printf("watch : Invalid Syntax\n");
			return ;
		}
	}
    int i=0;
    long long int initime=time(0),prev=-1,inter;
    char ch;
    nonblock(0);
	while(!i)
	{
		i=kbhit();
		inter=time(0);
		if((inter-initime)%tim==0 && prev!=inter)
		{
			prev=inter;
			finddirtysize();
		}
		if(i!=0)
		{
			ch=fgetc(stdin);
			if(ch=='q')
			{
				i=1;
			}
			else
			{
				i=0;
			}
		}
	}
    nonblock(1);
}