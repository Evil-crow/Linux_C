#ifndef _MAIN_H
#define _MAIN_H

struct user
{

};

int socket_creat(void);                                     //监听套接字的创建

void epoll_server(int listen_fd);                           //epoll+多线程函数

#endif