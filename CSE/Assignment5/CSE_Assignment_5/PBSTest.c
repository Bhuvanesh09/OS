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
    int pid1;
    if((pid1 = fork())==0)
    {
        int pid2;
        if((pid2 = fork())==0)
        {
        	// set_priority(atoi(argv[1]));
            dosomething(60);
            printf(1, "Exit 1\n");
        }
        else
        {
        	// set_priority(atoi(argv[2]));
            dosomething(60);
            printf(1, "Exit 2\n");
        }
    }
    else
    {
    	// set_priority(atoi(argv[3]));
        dosomething(60);
        printf(1, "Exit 3\n");
    }
    exit();
}
