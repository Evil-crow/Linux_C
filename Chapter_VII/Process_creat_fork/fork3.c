/* 孤儿进程的实现
 *
 * 顾名思义,孤儿进程就是指子进程还未结束,父进程已经结束的情况
 *
 * UNIX中,子进程没有父进程是不被允许的,所以,孤儿进程
 *
 * 就会被init进程收养,成为其(孤儿进程)父进程
 *
 * 原来init进程PID = 1
 *
 * 现在,在当前操作系统(Fedora 25)下,init进程为1578,1563等,存在多个init
 *
 * 孤儿进程的实现,主要依靠sleep函数
 *
 * 我的系统算法与示例不同,多数情况下,父进程优先
 */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char **argv)
{
   pid_t pid;                       /*获取PID的参数*/
   printf("Fork start!\n");
   pid = fork( );                   /*创建新进程并获取其PID*/

   switch(pid)
   {
      case 0:
         sleep(1);          /* 此语句用来睡眠,使得子进程后于父进程结束,研究子进程pid的变化*/
         printf("I am child process my pid is %d my parent process pid is %d\n",getpid( ),getppid( ));
         break;
      case -1:
         printf("Fork Error!\n");
         break;
      default:
         printf("I am parent process,my pid is %d, my parent process pid ios %d\n",getpid( ),getppid( ));
   }

   return 0;
}
