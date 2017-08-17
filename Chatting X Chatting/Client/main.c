#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include"main.h"
#include"struct_node_client.h"

int chat_status = 0;              //不进入私聊前,置为0                      //定义全局标识位,用于标识,是否处于私聊状态 

extern struct node_client recv_user;                                     //用于判定登录/注册情况,直接退出

void _error(const char *string,int line);

int main(int argc,char **argv)
{
    int sock_fd;                                //创建套接字
    pthread_t    thid;                          //创建线程ID

    system("clear");                            //运行程序清屏操作
    sock_fd = sock_fd_create( );
    //signal(SIGINT,SIG_IGN);                     //屏蔽Ctrl-C的意外信号
    if(sock_fd < 0)                             //创建用于连接的sock_fd
    {
        printf("\t\t\t\tError\n");
        exit(EXIT_SUCCESS);
    }
    pthread_create(&thid,NULL,(void *)_recv,sock_fd);          //开线程一直处于recv状态,进行信息的获取
    pthread_detach(thid);                                      //用于回收线程资源
    work(sock_fd);                                             //工作函数
    
    return 0;
}

void work(int sock_fd)
{  /*向work函数中传入的已经是进行过连接的套接字,可以用于实现C/S通信*/
    sign_in(sock_fd);                                    //进行登录注册操作
    if(recv_user.consumer.choice_sign == 2)              //如若是注册,完成后直接退出,是登录则会成功进入聊天室
    exit(0);
    /*此处无需放置清屏函数,所有的的清屏函数,放在后面的子菜单函数里面*/
    chat_data(sock_fd);                                //登录后进行操作的函数  
}

void _error(const char *string,int line)
{
    printf("\t\t\t\tError line:%d",line);
    perror(string);
    printf("\n");
}