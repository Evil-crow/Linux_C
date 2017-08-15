#ifndef _WORK_H
#define _WORK_H

#define MAX_STR           30
#define MAX_MESSAGE       45

struct friends_operation
{
    int   FRIEND_ADD;               //添加好友
    int   FRIEND_DEL;               //删除好友
    int   FRIEND_SHIELD;            //屏蔽好友
};
struct sign
{
    int choice_sign;                        //进行登录选择
    char username[MAX_STR];
    char passwd1[MAX_STR];                  //登录密码
    char passwd2[MAX_STR];                  //注册密码
    int  result;                            //登录注册包回馈的结果
};
struct data
{
    int                         choice_data;                        //进行操作选择
    int                         friends_status;                     //表示好友状态,0/离线,1/在线
    char                        friends_name[MAX_STR];              //想要发送消息的好友姓名
    struct friends_operation    friends_choice;
    char                        chatting_group[MAX_STR];            //聊天群名
    char                        message[MAX_MESSAGE];               //要发送的消息

};
struct node_client
{
    int flag;                               //用于标记是用来进行登录注册还是进行数据操作
    int decision;                           //表示是否同意请求 Y/同意,n/不同意
    struct sign consumer;                   //登录时使用结构体
    struct data person;                     //进行操作时使用的结构体
};
#endif