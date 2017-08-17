#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include"struct_node_server.h"
#include"Linkedlist.h"

extern list *pHead;                                                //全局的链表

extern void _error(const char *string,int line);                        //自定义判错函数

void friend_managment(int conn_fd,struct node_server user)
{
    list *temp;                                              //进行在新用户查找的节点
    char ch;                                                 //用于判断好友为空的情况
    FILE *fp;
    FILE *sp;                                                //备份文件
    char str[200] = "/home/Crow/Public/Information/";
    char pwd[200];                                           //获取绝对路径
    char str_name[30]; 
    char str_path[100];                                            //保存目标姓名
    switch(user.my_firend.choice_friend)
    {
        case 1:                                                    //进行私聊的情况
            break;
        case 2:                                                    //进行添加好友选项
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(user.consumer.username,temp->name);
            temp = linkedlist_seek_username(pHead,user.my_firend.friends_name);
            if(temp == NULL)
            {
                printf("离线模式\n");
                break;
            }
            send(temp->conn_fd,&user,sizeof(struct node_server),0);          //将添加好友的信息发给目标好友
            printf("已将信息发至目标好友\n");
            break;
        case 3:                                                    //表示处理添加好友选项
            if(user.decision == 1)                                 //表示同意请求
            {
                printf("对方已经同意添加好友的请求\n");
                char str1[200],str2[200];
                strcpy(str1,str);
                strcat(str1,user.consumer.username);
                strcat(str1,"/friends_list");
                printf("%s\n",str1);
                fp = fopen(str1,"a+");
                if(fp == NULL)
                    _error("fopen",__LINE__);
                fprintf(fp,"%s\n",user.my_firend.friends_name);       //写入好友列表
                fclose(fp);
                strcpy(str2,str);
                strcat(str2,user.my_firend.friends_name);
                strcat(str2,"/friends_list");
                fp = fopen(str2,"a+");
                if(fp == NULL)
                    _error("fopen",__LINE__);
                fprintf(fp,"%s\n",user.consumer.username);
                fclose(fp);
            }
            break;
        case 4:                                                      //进行好友列表的显示
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(str_path,str);
            strcat(str_path,temp->name);
            strcat(str_path,"/friends_list");                        //获取到好友列表路径
            printf("%s\n",str_path);                                 //检查路径
            fp = fopen(str_path,"r+");
            if((ch = fgetc(fp)) == EOF)
            {
                strcpy(user.my_firend.friends_name,"暂无好友,快去勾搭小姊姊吧(ಡωಡ)\n");
                send(conn_fd,&user,sizeof(struct node_server),0);    //返回空信息
                break;
            }
            fseek(fp,0L,0);                                          //文件指针回到文件开头处
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",str_name);                          //将好友列表读至暂存区内
                strcpy(user.my_firend.friends_name,str_name);        //拷贝好友名至结构体中
                send(conn_fd,&user,sizeof(struct node_server),0);    //进行内容的发送
            }
            fclose(fp);
            printf("内容发送完成!\n");
            break;
        case 5:                                                      //进行好友删除操作
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);
            strcpy(str_path,str);
            strcat(str_path,temp->name);
            chdir(str_path);                                         //切换至第一个用户目录下
            printf("%s\n",str_path);
            fp = fopen("friends_list","r+");                         //使用r+打开,进行好友删除
            sp = fopen("a","w+");                                    //创建备份文件
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",str_name);                         //将用户名读取到临界字符串中
                if(strcmp(str_name,user.my_firend.friends_name) == 0)   //如果是要删除的好友,则跳过
                    continue;
                fprintf(sp,"%s\n",str_name);                        //若不是,则写入新的的文件中
            }
            fclose(fp);
            fclose(sp);
            remove("friends_list");
            rename("a","friends_list");
            printf("删除成功!\n");
            memset(str_path,0,sizeof(str_path));                    //置空,重新对其进行处理
            strcpy(str_path,str);
            strcat(str_path,user.my_firend.friends_name);           
            chdir(str_path);                                        //切换到第二个目录下
            fp = fopen("friends_list","r+");                         //使用r+打开,进行好友删除
            sp = fopen("a","w+");                                    //创建备份文件
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",str_name);                         //将用户名读取到临界字符串中
                if(strcmp(str_name,temp->name) == 0)   //如果是要删除的好友,则跳过
                    continue;
                fprintf(sp,"%s\n",str_name);                        //若不是,则写入新的的文件中
            }
            fclose(fp);
            fclose(sp);
            remove("friends_list");
            rename("a","friends_list");
        case 6:                                                     //表示进行的是,显示好友状态操作
            temp = linkedlist_seek_conn_fd(pHead,conn_fd);          //查找请求的用户名
            strcpy(str_path,str);  
            strcat(str_path,temp->name);
            chdir(str_path);                                        //切换工作目录
            fp = fopen("friends_list","r+");
            if((ch = fgetc(fp)) == EOF)
            {
                strcpy(user.my_firend.friends_name,"zero");         //不存在好友,则置空
                send(conn_fd,&user,sizeof(struct node_server),0);   //发包
                break;
            }
            fseek(fp,0L,0);                                         //文件指针回到起始处
            while(!feof(fp))
            {
                fscanf(fp,"%s\n",str_name);                         //读出用户名
                strcpy(user.my_firend.friends_name,str_name);       //填入好友名
                temp = linkedlist_seek_username(pHead,str_name);    //尝试查找在线用户
                if(temp == NULL)                                    //证明不在线
                    user.my_firend.friends_status = 0;              //标识位置0
                else
                    user.my_firend.friends_status = 1;              //在线则标识位置1
                send(conn_fd,&user,sizeof(struct node_server),0);   //服务端发包
            }
            fclose(fp);
            printf("好友状态判断完成\n");
            break;
    }
}