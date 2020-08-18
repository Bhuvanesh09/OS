#include "header.h"

void setenvv(char **c)
{
	if(size1==2)
	{
		c[2]="";
	}
	if(size1==1 || size1>3)
	{
		printf("Invalid input\n");
		return ;
	}
	if(setenv(c[1],c[2],1)!=0)
	{
		perror("Setenv");
	}
}

void unsetenvv(char **c)
{
	if(size1!=2)
	{
		printf("Invalid input\n");
		return ;
	}
	if(unsetenv(c[1])!=0)
	{
		perror("Unsetenv");
	}
}