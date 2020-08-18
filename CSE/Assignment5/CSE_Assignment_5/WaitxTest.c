#include "types.h"
#include "user.h"

void dosomething(int x)
{
    for(int i=0;i<x*1e6;i++)
    {
        volatile int x = 1;
        x++;
    }
}

int 
main(int argc, char * argv[])
{
	dosomething(atoi(argv[1]));
	int pid;
	if((pid=fork())<0)
	{
		exit();
	}
	if(pid==0)
	{
		dosomething(atoi(argv[2]));
		sleep(atoi(argv[1]));
	}
	else
	{
		int x,y;
		waitx(&x,&y);
		printf(1,"Waiting Time = %d , Running Time = %d\n",x,y);
	}
	exit();
}