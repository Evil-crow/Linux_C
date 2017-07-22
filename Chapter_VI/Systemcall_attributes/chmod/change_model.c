#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
   int mode;                              //进行修改的权限

   int mode_u;                            //user权限
   
   int mode_g;                            //group权限
   
   int mode_o;                            //other权限

   if(argc > 3)                           //传参不符合要求,错误退出
   {
      printf("Argc Error!");
      exit(-1);
   }

   mode = atoi(argv[1]);                 //atoi函数进行mode八进制值的获取

   mode_u = mode/100;                    //user权值的获取

   mode_g = mode%100/10;                 //group权值的获取

   mode_o = mode%100%10;                 //other权值的获取
   
   if(mode > 777 || mode < 000)
   {
      printf("mode Error!");
      exit(-1);
   }

   mode  = mode_u*8*8 + mode_g*8 + mode_o;   //使用chmod函数.mode_t mod 需要十进制整数

   if(chmod(argv[2],mode) == -1)             //调用chmod函数进行权值的修改
   {
      printf("change mode Error!");
      exit(-1);
   }

   return 0;
}
