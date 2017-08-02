/* 此代码是为了实现进程的创建函数,线程操作,在类UNIX下基本都是使用POSIX标准
 *
 * 所提供的<pthread.h>库,所以基本上都是调用API,然后链接库,这种编程习惯还不是很熟悉
 *
 * get_thid( )函数,是线程创建后要进行调用的函数,尤其注意pthread_create函数的用法
 *
 * 认真掌握,pthread_create函数中各参数的不同含义,进行正确合理的使用
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int *get_thid(void);

int main(int argc,char **argv)
{
    pthread_t thid;

    printf("parent pthread is me,my thid is %d\n",pthread_self( ));
    if(pthread_create(&thid,NULL,(void *)get_thid,NULL) != 0)
    {
        printf("Error!\n");
        return 0;
    }
    sleep(1);
    return 0;
}
int *get_thid(void)
{
    pthread_t thid;

    thid = pthread_self( );
    if(thid < 0)
    {
        printf("Error!\n");
        exit(0);
    }
    printf("I'm child pthread,my thid is %d\n",thid);
    return NULL;
}
