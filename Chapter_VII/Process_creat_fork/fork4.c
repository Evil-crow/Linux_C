/* 僵尸进程的创建与测试
 *
 * 所谓僵尸进程,听上去真的是耸人听闻
 *
 * 实际上,类似于孤儿进程,不过正好相反,僵尸进程是子进程更早的结束
 *
 * 但是,因为父进程没有收到静子进程结束的信息
 *
 * 所以,子进程还不能算是真正的结束,
 *
 * 也就有所谓的"僵尸"
 *
 * 至于处理僵尸进程的方法,总结以下有三种
 *
 * 1.Kill僵尸爸爸,再重新start就可以了
 *
 * 2.在fork前设置信号,可避免僵尸进程
 *
 * 3.连续使用两次fork(),由孙子进程进行任务,子进程直接退出,
 *
 * 孙子交由init收养,init处理一切收尸情况
 */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
   pid_t pid;
   int i = 5;
   
   pid = fork( );
   switch(pid)
   {
      case 0:
         printf("I am child process my pid is %d,i = %d\n",getpid( ),i++);
         _exit(0);
         break;
      case -1:
         printf("Fork Error!");
         break;
      default:
         sleep(5);
         printf("I am parent process my pid is %d,i = %d\n",getpid( ),i++);
         
   }

   return 0;
}
