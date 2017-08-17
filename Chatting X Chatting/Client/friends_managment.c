#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include"struct_node_client.h"
void chatting_with_friend(int sock_fd)
{
    char ch;                                                   //实现按任意键退出
    struct node_client user;                                   //进行处理的结构体

    user.flag = 2;                                             //表示进行好友项目的操作
    user.my_firend.choice_friend = 1;                          //表示进行私聊
}

void add_new_friend(int sock_fd)
{
    char ch;
    struct node_client user;
    
    user.flag = 2;                                             //进行好友相关操作
    user.my_firend.choice_friend = 2;                          //表示添加好友操作
    system("clear");
    printf("请输入要添加的好友姓名:\n");
    scanf("%s",user.my_firend.friends_name);                   //存储要添加的好友姓名
    printf("准备发送中!\n");
    send(sock_fd,&user,sizeof(struct node_client),0);          //进行添加好友请求的发送
    printf("添加好友请求已发送\n");
    printf("按任意键返回~\n");
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void print_friend_list(int sock_fd)
{
    char ch;
    struct node_client user;
    
    user.flag = 2;                                            //进行好友操作
    user.my_firend.choice_friend = 4;                         //获取好友列表选项
    printf("您的联系人列表:\n");
    send(sock_fd,&user,sizeof(struct node_client),0);          //发送信息包
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void del_friend(int sock_fd)
{
    char ch;                                                   //进行任意键退出
    struct node_client user;
    
    user.flag = 2;                                             //进行好友操作
    user.my_firend.choice_friend = 5;                          //表示进行删除好友操作
    printf("请输入你要删除的好友:\n");
    scanf("%s",user.my_firend.friends_name);                   //存取删除好友的姓名
    printf("你确定要删除此好友吗?(0/1)  ");
    scanf("%d",&user.decision);                                //获取到用户的选择
    send(sock_fd,&user,sizeof(struct node_client),0);          //发送信息包
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void display_friend_status(int sock_fd)                         //查看好友状态
{
    char ch;                                                    //按任意键退出
    struct node_client user;                 
    user.flag = 2;                                              //进行的是好友操作
    user.my_firend.choice_friend = 6;                           //表示显示好友列表操作
    printf("好友在线情况如下:\n");
    send(sock_fd,&user,sizeof(struct node_client),0);          //发送请求
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}