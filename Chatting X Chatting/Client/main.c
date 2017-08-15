#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include"main.h"
#include"work.h"

void _error(const char *string,int line);

int main(int argc,char **argv)
{
    int sock_fd;                                //创建套接字
    pthread_t    thid;                          //创建线程ID

    sock_fd = sock_fd_create( );
    if(sock_fd < 0)                             //创建用于连接的sock_fd
    {
        printf("Error\n");
        exit(EXIT_SUCCESS);
    }
    work(sock_fd);                                             //工作函数
    pthread_create(&thid,NULL,(void *)_recv,sock_fd);          //开线程一直处于recv状态,进行信息的获取
    pthread_detach(thid);                                      //用于回收线程资源
    
    return 0;
}

void work(int sock_fd)
{  /*向work函数中传入的已经是进行过连接的套接字,可以用于实现C/S通信*/
    sign_in(sock_fd);                                    //进行登录注册操作
    printf("\n登陆中...\n");
    //chat_data(sock_fd);                                //登录后进行操作的函数  
}

void _error(const char *string,int line)
{
    printf("Error line:%d",line);
    perror(string);
    printf("\n");
}