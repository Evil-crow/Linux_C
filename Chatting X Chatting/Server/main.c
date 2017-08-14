#include<stdio.h>
#include"main.h"

int main(int argc,char **argv)
{
    int listen_fd;                              //监听套接字
    listen_fd = listen_fd_create( );             //创建监听套接字
    epoll_server(listen_fd);                    //epoll+多线程

    return 0;
}