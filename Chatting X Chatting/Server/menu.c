#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include"menu.h"
#include"main.h"
#include"Linkedlist.h"
#include"struct_node_server.h"

struct epoll_event epoll_ev;            //epoll_event类型结构体,用于注册事件使用

void sign_register(int sock_fd,struct node_server user);

void friend_managment(int conn_fd,struct node_server user);

void group_managment(int conn_fd,struct node_server user);

extern int epoll_fd;                       //在epoll_server中定义,此处为引用

extern void _error(const char *string,int line);

extern char *get_time(void);

extern list *pHead;

void menu(int conn_fd)
{
    struct node_server user;                   //进行接受的结构体
    int ret;                                   //处理返回值
    list *temp;
    //memset(&user,0,sizeof(user));            //如若置空,以后多次交互不好取出信息 
       
    ret = recv(conn_fd,&user,sizeof(struct node_server),0);
  
    if(ret <= 0)
    {
        if(ret < 0)                         //表示接受失败
            _error("recv",__LINE__);
        if(ret == 0)                     //表示对方已经关闭连接
        {
            if(pHead->next != NULL)
            {
                temp = linkedlist_seek_conn_fd(pHead,conn_fd);
                FILE *sp;
                char str[200];
                strcpy(str,get_time( ));
                sp = fopen("/home/Crow/Public/Information/server_log","a+");
                fprintf(sp,"%s log out : %s\n",temp->name,str);
                fclose(sp);
                epoll_ctl(epoll_fd,EPOLL_CTL_DEL,conn_fd,NULL);      //从epoll注册表中删除该事件,并关闭套接字.
                linkedlist_del(pHead,temp->name);
                close(conn_fd);
            }
            else
            {
                epoll_ctl(epoll_fd,EPOLL_CTL_DEL,conn_fd,NULL);      //从epoll注册表中删除该事件,并关闭套接字.
                close(conn_fd);
            }
        }
    }
    if(ret > 0)
    {
        while(ret != sizeof(struct node_server))
            ret = recv(conn_fd,&user,sizeof(struct node_server),0);
        switch(user.flag)
        {
            case 1:                                       //表示执行登录操作
                sign_register(conn_fd,user);              //进行登录注册的函数
                break;
            case 2:                                       //表示进行好友操作
                friend_managment(conn_fd,user);           //进行数据操作通信的函数
                break;
            case 3:
                group_managment(conn_fd,user);            //进行聊天群的处理
                break;
        }
    }
    
    struct epoll_event ep_ev;                            //在工作任务结束之后,进行再注册,使该事件可以再次被报告
    ep_ev.data.fd = conn_fd;
    ep_ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(epoll_fd,EPOLL_CTL_MOD,conn_fd,&ep_ev);
}