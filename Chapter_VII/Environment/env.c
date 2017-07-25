/* env.c代码对于环境变量的实现,是依靠main函数中的传参
 *
 * envp获取到的
 *
 */

#include<stdio.h>
#include<malloc.h>
int main(int argc,char **argv,char **envp)
{
   int i;

   for(i = 0;i < argc;i++)
   {
      printf("argv[%d] is %s\n",i,argv[i]);
   }

   for(i = 0;i < argc;i++)
   {
      printf("%s\n",envp[i]);
   }

   return 0;
}
