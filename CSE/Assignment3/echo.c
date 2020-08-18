#include"header.h"

void echox(char **c)
{
	if(strcmp(c[1],"")==0)
	{
		printf("\n");
		return ;
	}
	if(c[1][0]=='"' && c[size1-1][strlen(c[size1-1])-1]=='"')
	{
		for(int i=1;i<size1;i++)
		{
			for(int j=0;j<strlen(c[i]);j++)
			{
				if(!((i==1 && j==0) || (i==size1-1 && j==strlen(c[size1-1])-1)))
				{
					printf("%c",c[i][j]);
				}
			}
			printf(" ");
		}
		printf("\n");
	}
	else
	{
		for(int i=1;i<size1;i++)
		{
			printf("%s ",c[i]);
		}
		printf("\n");
	}
}