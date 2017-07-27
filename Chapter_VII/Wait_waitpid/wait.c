/* wait,waitpid函数在进行进程处理中,具有很重要的作用,
 *
 * 因为牵扯到子父进程,必然会牵扯到先后的问题,而且,
 *
 * 孤儿进程,僵尸进程也是常有的事
 *
 * 而为了更好地解决子父进程的调度问题
 *
 * 可以使用wait函数,以之来解决进程调度的问题
 *
 * 仔细理解wait的用法以及其结束字段中的信息,以及使用宏取出其中的信息
 *
 */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int argc,char **argv)
{
   int status;                              /*用来记录wait返回值*/
   int pid;                                 /*记录fork的返回值*/
   int exit_code,k;                           /*设置退出码,用于获取结束信息*/

   printf("fork start!\n");
   pid = fork( );                           /*新进程已经建立,父子进程并行,或者说是操作系统对进程的快速切换*/
   
   switch(pid)
   {
      case 0:
         k = 4;                             /*之后子进程循环操作,使父进程阻塞的依据*/
         exit_code = 45;                    /*子进程设置退出码,之后可以在父进程中获取*/
         break;
      case -1:
         printf("Error!");
         break;
      default:
         exit_code = 0;
         break;
   }

   if(pid != 0)
   {
      int status;                          /*此即为wait函数中的statloc变量,用于获取退出码*/
      pid_t  child_pid;                   /*wait函数的返回值,用于取得结束的子进程的pid*/

      child_pid = wait(&status);           /*获取到退出码(退出码中储存着退出时的信息,是一个字段,可用宏取出其中信息)以及结束的子进程的pid*/

      printf("Child process has exited!It's pid is %d\n",child_pid);
      if(WIFEXITED(status))
      {
         printf("Child process has exited,It's exit_code is %d\n",WEXITSTATUS(status));   //WEXITSTTUS宏用来获取exit函数低8位
      }
      else
         printf("Child process exit abnormally\n");
   }

   while(k--)
   {
      sleep(2);
      printf("Child process is running!\n");
   }
   exit(exit_code);
}

/* wait,waitpid函数的主要作用,用于进行子父进程的调度问题上
 *
 * wait.c程序设计思路
 *
 * fork前,声明exit_code,k变量
 *
 * fork新建子进程后,子父进程并行进行
 *
 * 进入Switch进行判断,
 *
 * 子进程被设置了循环次数
 *
 * 子父进程获得了exit_code
 *
 * 两个进程,又同时进入了之后的判断中
 * 
 * 父进程获得了子进程结束的退出码,status储存在其中
 *
 * 同时也使用child_pid get到了子进程的PID
 *
 * 进行判断,此处就使用到了wait中奇妙的宏
 *
 * 用WIFEXITED获取退出信息
 * 用WIFEXITSTATUS获取退出码中低8位,即exit_code
 * 最后编译完成后,程序运行期间,再开一个终端
 * ps -aux可以观察到父进程处于 S,即阻塞状态(等待状态)
 * 至于wait,waitpid的详细,我会在Blog中说明 *
 */
 
