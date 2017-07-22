#include<errno.h>                                               //errno
#include<string.h>                                              //strerror( )
#include<stdio.h>                                               
#include<sys/types.h>                                           //open( ),creat( )
#include<sys/stat.h>                                            //...
#include<fcntl.h>                                               //...
#include<unistd.h>
#include<stdlib.h>                                              //exit( )
int main(int argc,char **argv)
{
   if(argc > 2)                                                  //判断输入的参数
   {
      printf("Error! Argc is too much!");
      exit(0);
   }
   int fp;                                                       //定义之后使用的文件描述符

   fp = open(argv[1],O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);         //open方式打开,新建文件,若已经存在,则会报错,文件权限664
   //fp = creat(argv[1],S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);                     //creat系统调用新建文件,已经存在的文件会进行覆盖
   
   if(fp == -1)                                                 //open与creat函数调用失败
   {
      printf("Creat Error!\n");
      //perror("open");                                         //perror显示错误
      printf("%s        %d\n",strerror(errno),errno);           //strerror函数显示错误,并显示错误码
      exit(0);
   }
   else
      printf("Creat new file successfully!");                   //成功新建文件

   return 0;

}
