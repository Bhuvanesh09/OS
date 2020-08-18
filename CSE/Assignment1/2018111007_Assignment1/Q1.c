#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
void reversestring(char *c,int size)
{
	int i=0,j=size-1;
	char ch;
	while(i<j)
	{
		ch=c[i];
		c[i]=c[j];
		c[j]=ch;
		i++;
		j--;
	}
}
int main(int argc,char* argv[])
{
	char *prstr;

	if(argc!=2)
	{
		prstr="No path given\n";
		write(1,prstr,strlen(prstr));
		return 0;
	}

	char filen[1000]="Assignment/";
	int j,i=strlen(argv[1])-1;
	while(i>=0 && argv[1][i]!='/'){i--;}
	for(j=11,i=i+1;i<strlen(argv[1]);i++,j++)
	{
		filen[j]=argv[1][i];
	}
	filen[j]='\0';

	int fd1,fd2;

	if(mkdir("Assignment",S_IRUSR | S_IWUSR | S_IXUSR)==0)
	{
		prstr="Directory 'Assignment' Created\n";
		write(1,prstr,strlen(prstr));
	}
	else
	{
		perror("Assignment ");
	}

	fd1=open(argv[1],O_RDONLY);

	if(fd1<0)
	{
		perror("Input file ");
		return 0;
	}

	fd2=open(filen,O_WRONLY | O_CREAT,S_IRUSR | S_IWUSR);

	if(fd2<0)
	{
		perror("Output file ");
		close(fd1);
		return 0;
	}
	int prev=-1,total=lseek(fd1,0,SEEK_END),packsize=1e4,poi=((total/packsize)*packsize),rem=total%packsize,doneper,size;
	char arr[12];
	lseek(fd1,poi,SEEK_SET);
	char c[packsize+5];
	read(fd1,c,rem);
	reversestring(c,rem);
	write(fd2,c,rem);
	while(poi>0)
	{
		poi-=packsize;
		lseek(fd1,poi,SEEK_SET);
		read(fd1,c,packsize);
		reversestring(c,packsize);
		write(fd2,c,packsize);
		doneper=((((total-poi)*1.0)/(1.0*total))*100);
		if(doneper==prev)
		{
			continue;
		}
		prev=doneper;
		if(doneper==0)
		{
			size=1;
			arr[0]=48;
		}
		else
		{
			size=0;
			while(doneper>0)
			{
				arr[size]=doneper%10+48;
				size++;
				doneper/=10;
			}
		}

		prstr="Percentage of file copied = ";
		write(1,prstr,strlen(prstr));

		for(i=size-1;i>=0;i--)
		{
			write(1,&arr[i],1);
		}

		prstr="%\r";
		write(1,prstr,strlen(prstr));

	}

	prstr="Percentage of file copied = 100%\n";
	write(1,prstr,strlen(prstr));

	close(fd1);
	close(fd2);

	return 0;
}