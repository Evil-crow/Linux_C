#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include"struct_node.h"

extern void _error(const char *string,int line);

void sign_in(int sock_fd)
{
    struct node_client user;
    int ret;                                              //处理返回值
    user.flag = 1;                                        // 大结构体 中选择标记1 表示为 登录注册操作
    /*打印登录界面的菜单*/
    printf("===================================================================\n\n");
    printf("                     Welcome to Chatting_X_Chatting                \n\n");
    printf("                               1.登录                               \n\n");
    printf("                               2.注册                               \n\n");
    printf("                               0.退出                               \n\n");
    printf("===================================================================\n");
    printf("请输入你的选择:");
    scanf("%d",&user.consumer.choice_sign);
    switch(user.consumer.choice_sign)
    {
        case 1:                                                         //表示为登录操作
            printf("请输入你的用户名:");
            scanf("%s",user.consumer.username);                         //录入用户名
            printf("请输入密码:");
            system("stty -echo");                                       //设置不回显
            scanf("%s",user.consumer.passwd1);                          //录入登录密码
            system("stty echo");                                        //恢复回显
            send(sock_fd,&user,sizeof(struct node_client),0);
            break;
        case 2:                                                         //表示为注册操作
            printf("请输入要注册的用户名:");                               
            scanf("%s",user.consumer.username);                        //录入注册用户名
            //system("stty -echo");                                      //设置不回显
            printf("请输入密码:");
            scanf("%s",user.consumer.passwd1);                         //第一次输入密码
            printf("\n");
            printf("请在此输入密码:");
            scanf("%s",user.consumer.passwd2);                         //第二次确认输入密码
            printf("\n");
            //system("stty echo");                                       //恢复回显
            if(strcmp(user.consumer.passwd1,user.consumer.passwd2) == 0)
            ret = send(sock_fd,&user,sizeof(struct node_client),0);          //发送注册信息包
            if(ret < 0)
            {
                _error("send",__LINE__);
                exit(0);
            }
            if(strcmp(user.consumer.passwd1,user.consumer.passwd2) != 0)
            printf("两次密码输入不一致!\n");
            break;
        case 0:                                                         //表示为退出,不登入聊天室,与聊天室中的退出不同
            printf("\n打开了又不用人家,真的大丈夫吗?T^T\n");
            getchar( );
            exit(EXIT_SUCCESS);
            break;                                                     //完成客户端登录界面的退出,不需要与服务器发生交互.
    } 
}

