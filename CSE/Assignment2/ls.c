#include"header.h"

char *uid_to_name(uid_t uid)
{
	struct passwd *getpwuid(),*pw_ptr;
	static char numstr[10];
	if((pw_ptr=getpwuid(uid))==NULL)
	{
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
	{
		return pw_ptr->pw_name;
	}
}

char *gid_to_name(gid_t gid)
{
	struct group *getgrgid(),*grp_ptr;
	static char numstr[10];
	if((grp_ptr=getgrgid(gid))==NULL)
	{
		sprintf(numstr,"%d",gid);
		return numstr;
	}
	else
	{
		return grp_ptr->gr_name;
	}
}

void printdir(char *c,int f)
{
	struct dirent *de;
	DIR *dr=opendir(c);
	if(dr==NULL)
	{
        printf("Could not open directory %s\n",c); 
		return ;
	}
	while((de=readdir(dr))!=NULL)
	{
		if(f)
		{
			if(de->d_name[0]!='.')
			{
				printf("%s\n",de->d_name);
			}
		}
		else
		{
			printf("%s\n",de->d_name);
		}
	}
	closedir(dr);
}

void lsl(char *c,int f)
{
	struct stat thestat;
	struct dirent *de;
	struct passwd *tf;
	struct group *gf;
	DIR *dr=opendir(c);
	if(dr==NULL)
	{
        printf("Could not open current directory\n"); 
		return ;
	}
	while((de=readdir(dr))!=NULL)
	{
		if(f)
		{
			if(de->d_name[0]!='.')
			{
				stat(de->d_name,&thestat);
				printf((thestat.st_mode & S_IRUSR) ? "\nr" : "\n-");
				printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
				printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
				printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
				printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
				printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
				printf((thestat.st_mode & S_IROTH) ? "r" : "-");
				printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
				printf((thestat.st_mode & S_IXOTH) ? "x" : "-");
				char *ctime();
				char *tmps=ctime(&thestat.st_mtime);
				tmps[strlen(tmps)-1]=' ';
				printf(" %d %s %s %d %s %s\n",(int)thestat.st_nlink,uid_to_name(thestat.st_uid),gid_to_name(thestat.st_gid),(int)thestat.st_size,tmps,de->d_name);
			}
		}
		else
		{
			stat(de->d_name,&thestat);
			printf((thestat.st_mode & S_IRUSR) ? "\nr" :"\n -");
			printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
			printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
			printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
			printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
			printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
			printf((thestat.st_mode & S_IROTH) ? "r" : "-");
			printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
			printf((thestat.st_mode & S_IXOTH) ? "x" : "-");
			char *ctime();
			char *tmps=ctime(&thestat.st_mtime);
			tmps[strlen(tmps)-1]=' ';
			printf(" %d %s %s %d %s %s\n",(int)thestat.st_nlink,uid_to_name(thestat.st_uid),gid_to_name(thestat.st_gid),(int)thestat.st_size,tmps,de->d_name);
		}
	}
	printf("\n");
	closedir(dr);
}