#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
int main(int argc,char **argv)
{
    int fd;
    
    printf("Process Start!\n");
    printf("Process uid is %d,euid is %d\n",getuid(  ),geteuid(  ));

    fd = open("test.c",O_RDWR);
    if(fd == -1)
        printf("Error!");
    else
        printf("open Suessfully!\n");

    close(fd);
    
    return 0;
}
