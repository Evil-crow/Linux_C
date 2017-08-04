/*  POSIX 下进程控制的实验程序残缺版 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include<stdlib.h>

#define MAX_CHILD_NUMBER 10                     /* 允许建立的子进程个数最大值 */

#define SLEEP_INTERVAL 2                        /* 子进程睡眠时间 */

int proc_number=0;                              /* 子进程的自编号，从0开始 */

void do_something();                            /*子进程调用函数*/

int main(int argc, char* argv[])
{
    int child_proc_number = MAX_CHILD_NUMBER;   /* 子进程个数最大个数 */
    int i, ch;
    pid_t  child_pid;                           /* 子进程ID */
    pid_t pid[10]={0};                          /* 存放每个子进程的id */
    if (argc > 1)                               /* 命令行参数第一个参数表示子进程个数*/
    {
        child_proc_number = atoi(argv[1]);      /*表示程序运行时main传入进程最大限制数量*/
        child_proc_number= (child_proc_number > 10) ? 10 :child_proc_number;

		/*进行最大进程数的录入,若超过10,则以10为基准*/
    }
    for (i=0; i < child_proc_number; i++) {
        /* 填写代码，建立child_proc_number个子进程要执行
        * proc_number = i;
        * do_something();
        * 父进程把子进程的id保存到pid[i] */
		 child_pid = fork( );
		 if(child_pid == 0)
		 {
			 proc_number = i;
			 do_something();
		 }
		 else if(child_pid > 0)
		 {
			//  proc_number = i;
			//  do_something( );
			 pid[i] = child_pid;
		 }
		 else
		 	printf("error\n");
    }
	/*
	for (i=0; i < child_proc_number; i++)
	{
		printf("pid :%d\n",pid[i]);
	}*/
    /* 让用户选择杀死进程，数字表示杀死该进程，q退出 */

	//printf("111111\n");
    while ((ch = getchar()) != 'q')
    {
        if (isdigit(ch))
        {
            /*  填写代码，向pid[ch-'0']发信号SIGTERM，
            * 杀死该子进程 */
			kill(pid[ch-'0'],SIGTERM);
        }
    }
    /* 在这里填写代码，杀死本组的所有进程 */
	//printf("11111111111\n");

	for(i = 0;i < child_proc_number;i++)
	{
		kill(pid[i],SIGTERM);
	}

	//printf("1111111111\n");

    return 0;
}
void do_something( )
{
	while(1)
	{
    	printf("This is process No.%d and its pid is %d\n",proc_number,  getpid());
    	sleep(SLEEP_INTERVAL); // 主动阻塞两秒钟
	}
}
