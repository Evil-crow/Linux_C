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
                //groups_managment(sock_fd);
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
        printf("\t\t\t\t===================================================================\n\n\n");
        printf("\t\t\t\t                          1.发起聊天                                \n\n\n");
        printf("\t\t\t\t                          2.添加好友                                \n\n\n");
        printf("\t\t\t\t                          3.好友列表                                \n\n\n");
        printf("\t\t\t\t                          4.删除好友                                \n\n\n");
        printf("\t\t\t\t                          5.好友状态                                \n\n\n");
        printf("\t\t\t\t                          0.返回主菜单                              \n\n\n");
        printf("\t\t\t\t===================================================================\n");
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
            case 0:                                                       //返回主菜单
                return ;
        }
    }
}