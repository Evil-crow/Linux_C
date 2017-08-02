/* 理解fork( )之后,子父进程(勉强说是交替进行吧,因为例子的关系)
 *
 * 实际上,子父进程是随机的,无规律的,主要看系统的调度算法*/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc,char **argv)
{
   pid_t pid;
   int k;
   char *s;
  /* printf("Fork start!");*/
   printf("Fork start!\n");
   pid = fork( );

   switch(pid)
   {
      case 0:
         s = "I'm child process! my pid is ,my father pid is\n";
         k = 3;
         break;
      case -1:
         printf("Error!");
         break;
      default:
         /*sleep(1);*/
         k = 5;
         s = "I'm parent process!my pid is ,my parent pid is\n";
         break;
   }
   while(k--)
   {
      printf("%s\n%d\n",s,k);
      sleep(2);
   }

   return 0;
}
