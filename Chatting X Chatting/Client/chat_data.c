#include<stdio.h>
#include<stdlib.h>
#include"chat_data.h"
#include"friends_managment.h"
#include"groups_managment.h"

void chat_data(int sock_fd)
{
    int ret;                                                //用于处理返回值                                         //设置为信息处理结构体
    int choice;
    system("clear");                                        //进行清屏操作
    while(1)
    {
        system("clear");                                    //清理无用信息
        printf("\t\t\t\t==================================================================\n");
        printf("\t\t\t\t                            主菜单                                 \n");
        printf("\t\t\t\t==================================================================\n\n\n");
        printf("\t\t\t\t                          1.好友管理                               \n\n\n");
        printf("\t\t\t\t                          2.群聊管理                               \n\n\n");
        printf("\t\t\t\t                          3.文件管理                               \n\n\n");
        printf("\t\t\t\t                          4.其他选项                               \n\n\n");
        printf("\t\t\t\t                          5.消息盒子                               \n\n\n");
        printf("\t\t\t\t                          0.退出                                  \n\n\n");
        printf("\t\t\t\t==================================================================\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                system("clear");
                friends_managment(sock_fd);
                break;
            case 2:
                system("clear");
                groups_managment(sock_fd);
                break;
            case 3:
                system("clear");
                //file_managment(sock_fd);
                break;
            case 4:
                system("clear");
                //others(sock_fd);
                break;
            case 5:
                system("clear");
                view_box(sock_fd);
                break;
            case 0:
                printf("\t\t\t\t每一次的离别,都是为了下一次的相遇!\n");
                getchar( );
                system("clear");
                exit(0);
        }
    }
}

void friends_managment(int sock_fd)
{
    int choice ;
    while(1)
    {
        printf("\t\t\t\t===================================================================\n");
        printf("\t\t\t\t                          好友管理菜单                               \n");
        printf("\t\t\t\t===================================================================\n");
        printf("\t\t\t\t                          1.发起聊天                                \n");
        printf("\t\t\t\t                          2.添加好友                                \n");
        printf("\t\t\t\t                          3.好友列表                                \n");
        printf("\t\t\t\t                          4.删除好友                                \n");
        printf("\t\t\t\t                          5.好友状态                                \n");
        printf("\t\t\t\t                          6.查看聊天记录                             \n");
        printf("\t\t\t\t                          0.返回主菜单                               \n");
        printf("\t\t\t\t===================================================================\n");
        printf("\t\t\t\t请输入选项:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                chatting_with_friend(sock_fd);
                break;
            case 3:
                print_friend_list(sock_fd);
                break;
            case 2:
                add_new_friend(sock_fd);
                break;
            case 4:
                del_friend(sock_fd);
                break;
            case 5:
                display_friend_status(sock_fd);
                break;
            case 6:
                view_chat_log(sock_fd);
            case 0:                                                       //返回主菜单
                return ;
        }
    }
}

void groups_managment(int sock_fd)
{
    int choice;
    while(1)
    {
        printf("\t\t\t\t=====================================================================\n");
        printf("\t\t\t\t                          群组管理菜单                                 \n");
        printf("\t\t\t\t=====================================================================\n");
        printf("\t\t\t\t                          1.发起群聊                                   \n");
        printf("\t\t\t\t                          2.创建群组                                   \n");
        printf("\t\t\t\t                          3.加入群组                                   \n");
        printf("\t\t\t\t                          4.群成员列表                                  \n");
        printf("\t\t\t\t                          5.群成员状态                                  \n");
        printf("\t\t\t\t                          6.查看聊天记录                                \n");
        printf("\t\t\t\t                          7.加入的群组列表                               \n");
        printf("\t\t\t\t                          8.退出群组                                    \n");
        printf("\t\t\t\t                          0.返回上一级                                  \n");
        printf("\t\t\t\t=======================================================================\n");
        printf("请输入选项:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:                                                         //发起群聊函数
                chatting_with_group(sock_fd);
                break;
            case 2:                                                         //创建群组
                create_new_group(sock_fd);
                break;
            case 3:                                                         //加入群组
                join_group(sock_fd);
                break;
            case 4:                                                         //显示群成员列表
                display_group_member(sock_fd);
                break;
            case 5:                                                         //群成员状态
                display_member_status(sock_fd);
                break;
            case 6:                                                         //聊天记录
                //view_group_chat_log(sock_fd); 
                break;
            case 7:                                                         //加入的群组
                display_joined_group(sock_fd);                             
                break;
            case 8:                                                         //退出群组
                del_group(sock_fd);
                break;
            case 0:                                                         //返回上一级菜单
                return;
        }
    }
}