#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

void _error(const char *err_string,int line);

int main(int argc,char **argv)
{
    struct stat temp;

    if(argc != 2)
    {
        printf("Error!\n");
        exit(0);
    }

    if(stat(argv[1],&temp) == -1)
    {
        _error("stat:",__LINE__);
        exit(1);
    }

    printf("device is : %d\n",temp.st_dev);
    printf("inode is: %d\n",temp.st_ino);
    printf("mode is : %o\n",temp.st_mode);
    printf("user ID is : %d\n",temp.st_uid);
    printf("group ID is : %d\n",temp.st_gid);

    return 0;
}

void _error(const char *err_string,int line)
{
    printf("Error line: %d\n",line);
    perror(err_string);

    exit(1);
}
