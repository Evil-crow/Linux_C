/* 此代码是使用perror来进行错误检查的
 *
 * 往perror中传入err_string,即可输出错误码中包含的信息
 *
 * 其中切记,此函数使用"w"打开文件,所以即使没有文件
 *
 * 也会新建文件,使得函数成立
 *
 */
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>

void _error(const char *err_string,int line)
{
    printf("Error:%d",line);
    perror(err_string);
}

int main(int argc,char **argv)
{
    FILE *fp;

    char *filename = "file.c";
    fp = fopen(filename,"w");
    if(fp != NULL)
    {
        printf("open successfully!");
    }
    else
    {
        _error("fopen",__LINE__);
    }

    return 0;
}
