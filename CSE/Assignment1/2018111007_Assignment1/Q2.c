#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
void checkperm(char *c,char *name)
{
	struct stat fileStat;
	stat(c,&fileStat);
	char *tmpstr;

	tmpstr="User has read permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IRUSR)? " : YES\n":" : NO\n");
	write(1,tmpstr,strlen(tmpstr));
	tmpstr="User has write permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IWUSR)? " : YES\n":" : NO\n");
	write(1,tmpstr,strlen(tmpstr));
	tmpstr="User has execute permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IXUSR)? " : YES\n\n":" : NO\n\n");
	write(1,tmpstr,strlen(tmpstr));

	tmpstr="Group has read permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IRGRP)? " : YES\n":" : NO\n");
	write(1,tmpstr,strlen(tmpstr));
	tmpstr="Group has write permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IWGRP)? " : YES\n":" : NO\n");
	write(1,tmpstr,strlen(tmpstr));
	tmpstr="Group has execute permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IXGRP)? " : YES\n\n":" : NO\n\n");
	write(1,tmpstr,strlen(tmpstr));

	tmpstr="Others have read permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IROTH)? " : YES\n":" : NO\n");
	write(1,tmpstr,strlen(tmpstr));
	tmpstr="Others have write permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IWOTH)? " : YES\n":" : NO\n");
	write(1,tmpstr,strlen(tmpstr));
	tmpstr="Others have execute permissions on ";
	write(1,tmpstr,strlen(tmpstr));
	write(1,name,strlen(name));
	tmpstr=((fileStat.st_mode & S_IXOTH)? " : YES\n\n":" : NO\n\n");
	write(1,tmpstr,strlen(tmpstr));
}
int checkrev(char *c1,char *c2,int size)
{
	for(int i=0;i<size;i++)
	{
		if(c1[i]!=c2[size-i-1])
		{
			return 1;
		}
	}
	return 0;
}
int main(int argc,char* argv[])
{
	char *c;

	if(argc!=4)
	{
		c="Invalid number of arguments\n";
		write(1,c,strlen(c));
		return 0;
	}

	write(1,"\n",1);
	checkperm(argv[1],argv[1]);
	checkperm(argv[2],argv[2]);
	checkperm(argv[3],argv[3]);

	char *tmpstr;

	int fd1=open(argv[1],O_RDONLY);
	if(fd1<0)
	{
		perror(argv[1]);
		return 0;
	}

	int fd2=open(argv[2],O_RDONLY);
	if(fd2<0)
	{
		perror(argv[2]);
		close(fd1);
		return 0;
	}

	int total=lseek(fd1,0,SEEK_END),packsize=1e4,poi2=((total/packsize)*packsize),rem=total%packsize,poi1=0;
	char c1[packsize+5],c2[packsize+5];

	if(lseek(fd2,0,SEEK_END)!=total)
	{
		tmpstr="File content is reverse of the other file : No\n";
		write(1,tmpstr,strlen(tmpstr));
		close(fd1);
		close(fd2);
		return 0;
	}

	lseek(fd1,poi1,SEEK_SET);
	lseek(fd2,poi2,SEEK_SET);
	read(fd1,c1,rem);
	read(fd2,c2,rem);
	c1[rem]=c2[rem]='\0';
	if(checkrev(c1,c2,rem))
	{
		tmpstr="File content is reverse of the other file : No\n";
		write(1,tmpstr,strlen(tmpstr));
		close(fd1);
		close(fd2);
		return 0;
	}
	poi1+=(rem-packsize);

	while(poi2>0)
	{
		poi1+=packsize;
		poi2-=packsize;
		lseek(fd1,poi1,SEEK_SET);
		lseek(fd2,poi2,SEEK_SET);
		read(fd1,c1,packsize);
		read(fd2,c2,packsize);
		c1[packsize]=c2[packsize]='\0';
		if(checkrev(c1,c2,packsize))
		{
			tmpstr="File content is reverse of the other file : No\n";
			write(1,tmpstr,strlen(tmpstr));
			close(fd1);
			close(fd2);
			return 0;
		}
	}

	tmpstr="File content is reverse of the other file : Yes\n";
	write(1,tmpstr,strlen(tmpstr));
	close(fd1);
	close(fd2);
	return 0;
}