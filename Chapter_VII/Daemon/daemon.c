/* 创建守护进程
 * 
 * 其实我对守护进程了解的也不是很彻底
 *
 * 守护进程,后台运行,其错误信息不会发送至当前用户操作终端
 *
 * 当前用户操作终端的信息也不会键入守护进程
 *
 * 实际上,守护进程的创建是类似的
 *
 * 基本操作步骤都相同
 *
 * 即实质上,就是把一个新建的进程改变成守护进程的过程
 *
 * 1.新建进程,并且结束父进程,使其被init收养
 *
 * 2.然后,setsid创建新的对话期
 *
 * 3.在子进程中创建新的会话
 *
 * 4.之后关闭不需要的文件描述符
 *
 * 5.改变当前目录为根目录
 *
 * 6.设置屏蔽字umask为0
 *
 * 7.处理SIGCHLD信号即可
 *
 */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<signal.h>
#include<time.h>
#include<syslog.h>
#include<sys/param.h>

int init_daemon(void)
{
   int pid;
   int i;

   /*忽略终端信号,忽略STOP信号*/
   signal(SIGTTOU,SIG_IGN);
   signal(SIGTTIN,SIG_IGN);
   signal(SIGTSTP,SIG_IGN);
   signal(SIGHUP,SIG_IGN);

   pid = fork( );
   if(pid > 0)
   {
      exit(0);            /*直接结束父进程*/
   }
   else if(pid < 0)
   {
      printf("Error!");
      return -1;
   }

   /*建立新的进程组,使得进程组,子进程成为其首进程,以脱离其原来的进程终端*/
   setsid( );

   /*再次建立一个子进程,同时结束父进程,保证进程不是进程组长,同时该进程无法再打开一个新的终端*/
   pid = fork( );
   if(pid > 0)
      exit(0);
   else if(pid < 0)
      return -1;

   /*关闭所有从父进程继承的不许要得文件描述符*/
   for(i = 0;i < NOFILE;close(i++));

   /*改变工作目录为/,使其不与其他的文件系统牵连*/
   chdir("/");

   /*将文件屏蔽字设置为0*/
   umask(0);

   /*忽略SIGGHLD信号*/
   signal(SIGCHLD,SIG_IGN);

   return 0;
}

int main(int argc, char **argv)
{
   time_t now;
   init_daemon( );
   syslog(LOG_USER|LOG_INFO,"测试守护进程!  \n");
   while(1)
   {
      sleep(8);
      time(&now);
      syslog(LOG_USER|LOG_INFO,"系统时间: \t%s\t\t\n",ctime(&now));
   }
}



/* 此程序运行后,并不会有任何反应,
 *
 * 当然只是表面上不会有反映
 *
 * 可以通过ps -aux进行当前进程情况的查看
 *
 * 可以看到./a.out的进程在运行
 *
 * 此即为后台的---守护进程
 *
 */
