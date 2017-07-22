#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void _error(const char *err_string,int line);
int main(int argc,char **argv)
{
    int m,n;

    if(argc != 4)
    {
        printf("error!\n");
        exit(0);
    }

    m = atoi(argv[2]);
    n = atoi(argv[3]);
    if(chown(argv[1],m,n) == -1)
    {
        _error("chown",__LINE__);
    }

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line:  %d\n",line);
    perror(err_string);
    exit(0);
}
