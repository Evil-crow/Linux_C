#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<dirent.h>

#define normal      0                                                                  //一般命令
#define in_put      1                                                                  //输入重定向1 >
#define out_put     2                                                                  //输出重定向1 <
#define In_put      3                                                                  //输入重定向2 >>
#define _pipe       4                                                                  //管道命令

void print_shell(void);                                                                //打印Shell提示符 

void get_command(char *);                                                              //获取命令输入

int explain_command(char *,char [ ][256]);                                           //解析输入的命令

void go_command(int ,char [ ][256]);                                                         //执行命令

int find_command(char *);                                                               //在指定路径中查找命令对应的可执行程序

int main(int argc,char **argv)
{
    char *command = NULL;                                                              //字符串用来暂时存储命令

    char parameter[100][256];                                                          //用来解析存储命令中的参数;

    int  count;                                                                        //用来记录命令参数个数

    int i;                                                                             //有二维数组,肯定需要进行循环的变量

    command = (char *)malloc(sizeof(char)*256);                                        //为命令输入分配256字符的字符串
    if(command == NULL)
    {   
        perror("malloc failed!\n");
        exit(1);
    }

    while(1)                                                                           //shell主体程序
    {
        print_shell(  );                                                               //打印shell提示符
        get_command(command);                                                          //获取用户输入命令
        if(strcmp("exit\n",command) == 0 || strcmp("logout\n",command) == 0)
            exit(0);
        for(i = 0;i < 100;i++)
            parameter[i][0] = '\0';                                                    //每次循环前二维字符串初始化
        count = 0;                                                                     //参数计数初始化
        count = explain_command(command,parameter);                                      //对命令的参数进行分析
        go_command(count,parameter);                                                   //执行命令
    }
    
    if(command != NULL)                                                                //释放动态分配的内存空间
        free(command);
    command = NULL;                                                                    //使指针指空,防止出现"野指针"

    return 0;
}
