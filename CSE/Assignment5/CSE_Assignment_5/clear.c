#include "types.h"
#include "stat.h"
#include "user.h"

void
clear()
{
	for(int i=0;i<61;i++)
	{
		printf(1,"\xa");
	}
}

int
main(void)
{
	clear();
	exit();
	return 0;
}