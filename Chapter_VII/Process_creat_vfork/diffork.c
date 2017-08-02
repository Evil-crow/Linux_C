/* vfork()可以算是一段历史时期内fork()的替代品,因为fork()类函数,实质是为了exec()而
 *
 * fork()之后立即exec(),使其拷贝的代价太大,才会有vfork()
 *
 * 但是vfork()很不安全,因为子父进程内存空间,堆栈信息是共享的
 *
 * 而且,exec/exit函数之前,是不能退出子进程的(当然子进程结束例外)
 *
 * 不调用exec/exit函数,最后会使得父进程结果很奇怪
 *
 * 而且,一般不建议在子进程中,对父进程中的变量,全局变量进行修改
 *
 * 虽然是允许的,但是,最重在实际应用中,会造成很多不必要的影响
 *
 * 最后关于return和exit还有不得不说的二三事,详见Blog
 *
 * 还有严重的情况就是,在子进程中需要父进程的调度,则互相等待,死锁
 */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int b = 5;
int main(int argc, char **argv)
{
   pid_t pid;
   int a = 3,i;
   pid = vfork( );                                  /*创建子进程*/
   /*pid = fork( );*/
   switch(pid)                                          /*进行pid判断*/
   {
      case 0:
         i = 3;
         while(i--)
         {
            a++;
            b++;
            sleep(1);
            printf("a = %d,b = %d\n",a,b);
         }
         
         _exit(0);                                        /*注意此处应该如何对子进程进行操作*/
         
         //return;
      case -1:
         printf("Error!");
         break;
      default:
         i = 5;
         while(i--)
         {
            a++;
            b++;
            sleep(1);
            printf("a = %d,b = %d\n",a,b);
         }
         break;
   }

   return 0;
}
