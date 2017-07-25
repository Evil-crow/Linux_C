/* Env.c中对于环境变量的实现是在于,系统中预定义的外部变量
 *
 * environ,打印其值即可获取到环境变量
 *
 */


#include<stdio.h>
#include<malloc.h>

extern char **environ;                  /*在别处定义的系统变量(预定义)*/

int main(int argc,char **argv)
{
   int i;

   for(i = 0;i < argc;i++)
   {
      printf("argv[%d] is %s\n",i,argv[i]);
   }

   for(i = 0;i < argc;i++)
   {
      printf("%s\n",environ[i]);
   }

   return 0;
}
