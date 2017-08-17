#ifndef _GROUP_MANAGMENT_
#define _GROUP_MANAGMENT_

/******************群聊管理子菜单函数********************/

void chatting_with_group(int sock_fd);

void bulid_new_group(int sock_fd);

void join_group(int sock_fd);

void del_group_member(int sock_fd);

void display_group_member(int sock_fd);

void display_groups(int sock_fd);


#endif