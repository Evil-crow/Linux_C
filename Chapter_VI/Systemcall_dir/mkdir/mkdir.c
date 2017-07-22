#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>

void _error(const char *err_string,int line);

int main(int argc,char **argv)
{
    int mode;
    if(argc != 3)
    {
        printf("Error!\n");
        exit(0);
    }

    mode = atoi(argv[2]);
    if(mkdir(argv[1],0644) == -1)
    {
        _error("mkdir",__LINE__);
    }

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line:  %d\n");
    perror(err_string);
    exit(0);
}
