#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>

void _error(const char *err_string,int line);

int main(int argc,char **argv)
{
    if(argc != 3)
    {
        printf("Error!\n");
        exit(0);
    }

    umask(0000);
    if(open(argv[1],O_CREAT|O_EXCL|O_TRUNC,0644) == -1)
    {
        _error("open",__LINE__);
    }
    umask(0007);
    if(open(argv[2],O_CREAT|O_EXCL|O_TRUNC,0644) == -1)
    {
        _error("open",__LINE__);
    }

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line:%d\n");
    perror(err_string);
    exit(0);
}

