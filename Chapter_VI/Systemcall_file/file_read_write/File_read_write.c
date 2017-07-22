#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<error.h>

void _error(const char *err_string,int line);

int file_read(int fd);

int main(int argc,char **argv)
{
    int fd;
    char str[] = "Hello World!";

    if(fd = open(argv[1],O_CREAT|O_RDWR|O_TRUNC,S_IRWXU) == -1)
        _error("open",__LINE__);
    else
        printf("successfully!");

    if(write(fd,str,strlen(str)) != strlen(str))
        _error("write",__line__);

    file_read(fd);

    printf("/*-----------------------------*/");
    if(lseek(fd,0,seek_end) == -1)
        _error("lseek",__line__);
    if(write(fd,str,strlen(str)) != strlen(str))
        _error("write",__line__);

    file_read(fd);

    close(fd);
    return 0;
}

void _error(const char *err_string,int line)
{
    printf("The error line:  %d",line);
    perror(err_string);
    exit(1);
}

int file_read(int fd)
{
    int length;
    char str[30];

    if(lseek(fd,0,SEEK_END) == -1)
        _error("lseek",__LINE__);
    if(length = lseek(fd,0,SEEK_CUR) == -1)
        _error("lseek",__LINE__);
    if(lseek(fd,0,SEEK_SET) == -1)
        _error("lseek",__LINE__);

    printf("The file length %d\n",length);

    if(read(fd,str,length) == -1 )
        _error("write",__LINE__);

    printf("%s\n",str);

    return 0;
}
