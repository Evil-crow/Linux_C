#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<dirent.h>
#include<errno.h>

void _error(const char *err_string,int file);

int main(int argc,char **argv)
{
    if(argc != 2)
    {
        printf("Error!\n");
        exit(0);
    }

    DIR *dir;

    struct  dirent *temp;
    if((dir = opendir(argv[1])) == NULL)
    {
        _error("opendir",__LINE__);
    }

    while((temp  = readdir(dir)) != NULL)
    {
        printf("%s\n",temp->d_name);
    }
    closedir(dir);

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line:%d\n",line);
    perror(err_string);
    exit(0);
}
