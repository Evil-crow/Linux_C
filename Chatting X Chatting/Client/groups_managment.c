#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include"struct_node_client.h"

extern char *get_time(void);

extern void change(char *str);                                      //进行时间内容的转换

void chatting_with_group(int sock_fd);                              //发起群聊函数

void create_new_group(int sock_fd)
{
    char ch;                                                        //用于任意键退出
    struct node_client user;
    user.flag = 3;                                                  //进行群组的操作
    user.my_group.choice_group = 2;                                          //创建群组

    printf("请输入你要创建的群组:");
    scanf("%s",user.my_group.group_name);                           //存入群组名
    printf("继续创建吗?(0/1)");
    getchar( );
    if((ch = getchar( )) == '1')
    {
        send(sock_fd,&user,sizeof(struct node_client),0);            //发送信息包
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;                                                     //按回车键返回菜单
    }
    getchar( );
    if((ch = getchar ( )) == '\n')
    return ;                                                          //返回菜单
}

void join_group(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 3;                                //加入群组的操作

    printf("请输入你想要加入的群组:");
    getchar( );
    scanf("%s",user.my_group.group_name);                         //录入想要加入的群组名
    printf("确定加入该群组吗?(0/1)");
    getchar( );
    if((ch = getchar( )) == '1')
    {
        send(sock_fd,&user,sizeof(struct node_client),0);           //发送信息包
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }  
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void display_group_member(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 4;

    printf("请输入群组名:");
    scanf("%s",user.my_group.group_name);
    send(sock_fd,&user,sizeof(struct node_client),0);           //发包
    printf("群组成员显示如下:\n");
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void display_member_status(int sock_fd)
{
    int ch;

    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 5;                                      //显示群组成员的状态

    printf("请输入群组名:");
    scanf("%s",user.my_group.group_name);
    send(sock_fd,&user,sizeof(struct node_client),0);
    printf("群组成员状态如下:\n");
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void display_joined_group(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;                                                 //表示是好友的操作
    user.my_group.choice_group = 7;                                //显示所有加入的群的操作

    printf("您所加入的群组以下:\n");
    send(sock_fd,&user,sizeof(struct node_client),0);
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}

void del_group(int sock_fd)
{
    int ch;
    struct node_client user;
    user.flag = 3;
    user.my_group.choice_group = 8;                                 //表示删除群组的操作

    printf("请输入想退出的群组:");
    scanf("%s",user.my_group.group_name);
    printf("确认退出吗?(0/1)");
    getchar( );
    if((ch = getchar( )) == '1')
    {
        send(sock_fd,&user,sizeof(struct node_client),0);
        getchar( );
        if((ch = getchar( )) == '\n')
        return ;
    }
    getchar( );
    if((ch = getchar( )) == '\n')
    return ;
}