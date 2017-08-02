#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
int main(void)
{
    FILE *fp;                             //定义文件指针

    char *filename = "test.c";            //决定要打开的文件名
    if(fp = fopen(filename,"r"))
    {
        printf("open Successfully!");
    }
    else
    {
        printf("Open Error!the errno is %d\n",errno);              //如果错误则输出错误码
    }

    return 0;
}

/* 通过进行手动处理
 *
 * 如果文件不存在,则错误码是2
 *
 * 如果用户没有打开文件的权限,则错误码是13
 *
 */
