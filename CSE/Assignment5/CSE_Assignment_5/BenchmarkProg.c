#include "types.h"
#include "user.h"

void somefunc(int x)
{
	if(x<0)
	{
		return ;
	}
	somefunc(x-1);
	somefunc(x-2);
}

int 
main(int argc, char * argv[])
{
	int pid = fork();
	if(pid < 0)
	{
		exit();
	}
	if(pid > 0)
	{
		int x,y;
		waitx(&x,&y);
		printf(1,"wtime = %d , rtime = %d\n",x,y);
		exit();
	}
	somefunc(30);
	sleep(200);
	int pid2 = fork();
	if(pid2 < 0)
	{
		exit();
	}
	if(pid2 > 0)
	{
		wait();
		exit();
	}
	somefunc(60);
	sleep(2000);
    exit();
}
