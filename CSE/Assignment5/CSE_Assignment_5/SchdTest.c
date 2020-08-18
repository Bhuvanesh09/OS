#include "types.h"
#include "user.h"

void dosomething(int x)
{
	for(int i=0;i<x;i++)
	{
		volatile int x = 1;
		x++;
	}
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
		printf(1,"Wait Time = %d , Run Time = %d\n",x,y);
		exit();
	}
	for(int i=0;i<atoi(argv[2]);i++)
	{
		dosomething(atoi(argv[1]));
		sleep(atoi(argv[3]));
	}
    exit();
}