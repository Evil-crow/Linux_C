/*strerror(int ),将错误码errno输入至strerror中
 *
 * 即可获取到其中的信息
 *
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

int main(void)
{
    FILE *fp;

    char *filename = "file.c";
    if(fp = fopen(filename,"r"))
    {
        printf("open successfully!");
    }
    else
    {
        printf("Error:%d %s\n",errno,strerror(errno));
    }

    return 0;
}
