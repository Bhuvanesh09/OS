#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc,char *argv[])
{
	struct proc_stat p;
	for(int i=1;i<argc;i++)
	{
		if(getpinfo(&p,atoi(argv[i])) < 0)
		{
			printf(1,"Not Found\n");
			exit();
		}
		printf(1,"--------------\npid = %d\nruntime = %d\nnumrun = %d\ncurr_queue = %d\n",p.pid,p.runtime,p.num_run,p.current_queue);
		for(int j=0;j<5;j++)
		{
			printf(1,"ticks [%d] = %d\n",j+1,p.ticks[j]);
		}
		printf(1,"--------------\n");
	}
	exit();
}