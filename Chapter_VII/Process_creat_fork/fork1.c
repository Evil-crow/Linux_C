/* 可以用来理解fork( )进程后,进程之间的相互联系
 *
 * 两个进程,子父进程,使分开并行的,可以通过其输出结果进行验证
 *
 * 而且,具体要分清子进程对父进程的那些内容实现了拷贝,具体理解
 *
 * 最直观的一个例子缓冲区,可通国一下程序理解           */

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char **argv)
{
   pid_t pid;
  /* printf("Fork start!");*/            /*子进程对缓冲区的数据实行了拷贝,虽然fork( )在printf之后*/
   printf("Fork start!\n");
   pid = fork( );
   printf("1111\n");
   switch(pid)
   {
      case 0:
         printf("I'm child process! my pid is %d,my father pid is%d\n",getpid( ),getppid( ));
         break;
      case -1:
         printf("Error!");
         break;
      default:
         sleep(1);
         printf("I'm parent process!my pid is %d,my parent pid is%d\n",getpid( ),getppid( ));
         break;
   }

   return 0;
}
