#include<stdio.h> 
#include<string.h> 
#include<fcntl.h> 
#include<errno.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include<dirent.h>
#include<time.h>
#include<sys/stat.h> 
#include<sys/wait.h>
#include<pwd.h>
#include<grp.h>
#include<termios.h>
#include<sys/select.h>

struct node
{
	int status,jobid;
	pid_t pid;
	char com[100];
};

extern int size,size1,histsize,jobsize;
extern char hist[25][10000],historypath[10000],path[10000],hostname[10000],path2[10000];
extern struct node jobs[10000];
extern char *user;
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void addtohistory(char *c);
void historyexe(char **c);
void handler();
void getcwdstr(char *arr);
char *getusername();
void gethname(char *arr);
void printterm(char *usr,char *host,char *path);
int makerel(char *path,char *home,char *path2);
void printdir(char *c,int f);
void lsl(char *c,int f);
int pinfo(char **args,char *home);
void execothers(char **c,int bg);
int executecommand(char** c,char *path,char *path2,char *home);
void takeinp(char** c);
void resetinp(char** inp);
void makeinp(char *inp,char **c);
void gethome(char *from,char *to);
void echox(char **c);
int kbhit();
void nonblock(int state);
void dirty(char **c);
void finddirtysize();
void inithistory(char *home);
void checkbg();
void handler1(int sig_num);
void handler2(int sig_num);
void setenvv(char **c);
void unsetenvv(char **c);
void execute_fg(char **c);
void execute_bg(char **c);
void kjob(char **c);
int redirection(char **c);
int itsredirection(char **c);
void piping(char *c,char *path,char *path2,char *home);
int itspipe(char **c);
int isup(char **c);
void uparrowk(char *user,char *hostname,int k,char *path2,char *lel);
void cronjob(char **c);
void job();
void ovkill(int f);