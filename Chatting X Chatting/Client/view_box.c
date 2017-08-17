#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<curses.h>
#include"chat_data.h"
#include "struct_node_client.h"

extern struct node_client recv_user;                    //_recv线程所收到的结构体

void view_box(int sock_fd)
{
    printf("消息盒子\n");
    if(recv_user.my_firend.choice_friend == 2)                //表明为添加好友请求
    {
        char ch;
        recv_user.decision = 1;
        recv_user.my_firend.choice_friend = 3;
        printf("%s 向您发送添加好友的请求,是否同意(0/1)?  ",recv_user.consumer.username);
        scanf("%d",&recv_user.decision);
        printf(" name : %s,friend_name : %s,decison:%d\n",recv_user.consumer.username,recv_user.my_firend.friends_name,recv_user.decision);
        send(sock_fd,&recv_user,sizeof(struct node_client),0);     //反馈包发送
        printf("已经发送!\n");
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }
//if( == 3)
//else   暂无消息
}