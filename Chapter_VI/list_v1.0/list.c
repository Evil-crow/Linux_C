/*
*CopyRight, (C) 2012
*ls命令很常用，但很少人知道内部实现，更别说自己来实现了
*本文目的为实现一个简单的ls命令：包括：a、l参数解析，文
*件、目录等属性解析，也是学习IO操作的好例子。
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>

int  do_ls(char *dir,char *filename,int lflag)
{
	int n;
	struct stat buf;
	char out[100];
	struct passwd *pw;
	struct group *gr;
	struct tm *t;

	if(lflag == 0)		//如果不带l参数，直接显示文件/目录名
	{
		printf("%s\t",filename);
		return 0;
	}
		
	if(lstat(dir,&buf)<0)
	{
		fprintf(stderr,"stat error:%s\n",strerror(errno));
		return -1;
	}

	switch(buf.st_mode & S_IFMT)		//获取字符串的属性：普通文件-、目录d、字符设备c、块设备b、管道文件p、连接文件l、套接字文件s
	{
	case S_IFREG:	
		printf("-");
		break;
	case S_IFDIR:	
		printf("d");
		break;
	case S_IFCHR:	
		printf("c");
		break;
	case S_IFBLK:	
		printf("b");
		break;
	case S_IFIFO:	
		printf("p");
		break;
	case S_IFLNK:	
		printf("l");
		break;
	case S_IFSOCK:	
		printf("s");
		break;
	}

	for(n=8;n>=0;n--)		//打印文件的读写属性：读r、写w、执行x、无权限-
	{
		if(buf.st_mode&(1<<n))
		{
			switch(n%3)
			{
			case 2:
				printf("r");
				break;
			case 1:
				printf("w");
				break;
			case 0:
				printf("x");
					break;
			default:
				break;
			}
		}
		else
		{
			printf("-");
		}
	}
	
	printf(" %d",buf.st_nlink);		//硬链接数，此链接非彼链接，指（包含）目录的个数，文件为1，目录起始为2，再加上目录里包含的目录个数（不递归，只一层）
	
	pw = getpwuid(buf.st_uid);		//所属用户名
	printf(" %s",pw->pw_name);		

	gr = getgrgid(buf.st_gid);		//所属组名
	printf(" %s",gr->gr_name);

	printf(" %ld",buf.st_size);		//字节计总大小

	t = localtime(&buf.st_atime);	//最后一次访问时间
	printf(" %d-%d-%d %d:%d"
		,t->tm_year+1900
		,t->tm_mon+1
		,t->tm_mday
		,t->tm_hour
		,t->tm_min);
   	printf(" %s ",filename);	
	   
	if(S_ISLNK(buf.st_mode))		//判断是否为链接，是返回真
	{
		printf(" -> ");
		if(readlink(filename,out,100)==-1)
		{
			//printf("readlink error\n");
		}
		printf("%s",out);
	}
	printf("\n");
	return 0;
}

int ls_prepare(char *w,int aflag,int lflag)		//ls的准备工作
{
	struct stat buf;		//man lstat可以看到此结构
	char name[100];	
	DIR *dir;		//类似打开文件的fd描述符
	struct dirent *pdr;		//man readdir可以看到此结构

	if(lstat(w,&buf)<0)		//获取文件/目录属性并赋值给buf，该函数和lstat一样，只是当w为链接时，指代他本身，并不存在文件
	{
		fprintf(stderr,"stat error:%s\n",strerror(errno));
		return -1;
	}
	if(S_ISDIR(buf.st_mode))	//判断是否为目录，是返回真
	{
		dir = opendir(w);		//打开目录
		while ((pdr = readdir(dir))!=NULL)	//读/遍历目录
		{
			if(aflag==0)	//如果不带a参数，越过以.开头的所有文件/目录
			{ 
				if(pdr->d_name[0]=='.')
					continue;
				memset(name,0,100);		
				strcpy(name,w);			//拷贝
				strcat(name,"/");		//追加
				strcat(name,pdr->d_name);
				do_ls(name,pdr->d_name,lflag);
			}else		//有a参数显示所有
			{
				memset(name,0,100);
				strcpy(name,w);
				strcat(name,"/");
				strcat(name,pdr->d_name);
				do_ls(name,pdr->d_name,lflag);
			}
		}
		closedir(dir);
	}else	//为文件则直接显示
	{
		do_ls(w,w,lflag);
	}
	
	return 0;
}

int main(int argc,char **argv)
{
	int aflag =0;
	int lflag =0;
	char c;
	int i;
	while((c = getopt(argc,argv,"al"))!=-1)	//解析命令行参数，即-/--后面的字符串和给定的字符串匹配，有未解析字母返回字母或问号（取决于第3个参数），否则返回-1
	{
		switch(c)		//此处仅匹配a（所有）和l（列表），即只支持参数a、l
		{
		case 'a':
			aflag =1;
			break;
		case 'l':
			lflag =1;
			break;
		default:
			break;
		}
	}
	if(argc == optind )			//optind系统变量，执行命令参数的个数（不包括命令，奇怪的是无参情况下他为1），判断argc是否为1，是则取当前路径，让我们显得更专业点
	{
		ls_prepare("./",aflag,lflag);
	}
	else
	{
		for(i=optind;i<argc;i++)		//所有目录都传进去
			ls_prepare(argv[i],aflag,lflag);
	}
	printf("\n");
	return 0;
}
