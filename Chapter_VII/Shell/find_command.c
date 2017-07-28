#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>

int find_command(char *command)
{
    DIR *Dir;                                                       //目录结构指针,类似于FILE*
    struct dirent *dir_command;
    char *path[ ] = {"./","/bin","usr/bin"};

    if(strncmp(command,"./",2) == 0)
    {
        command = command+2;
    }

    int i = 0;
    for(i = 0;i < 3;i++)
    {
        if((Dir = opendir(path[i])) == NULL)
        printf("Open dir failed!");
        while((dir_command = readdir(Dir)) != NULL)
        {
            if(strcmp(command,dir_command->d_name))
            {
                closedir(Dir);
                return 1;
            }
        }
        closedir(Dir);
        i++;
    }

    return 0;
}
