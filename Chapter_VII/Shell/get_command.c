#include<string.h>
#include<stdio.h>
#include<stdlib.h>
void get_command(char *str)
{
    int i;
    int len = 256;
    char ch;

    i = 0;
    ch = getchar( );
    if(ch == '\n')
    {
        return ;
    }
    while(ch != '\n')
    {
        str[i++] = ch;
        ch = getchar( );
    }
    
    if(i > len)
    {
        printf("Command isn't allowed!\n");
        exit(0);
    }
    if(strcmp(str,"^C") == 0)
    {
        exit(0);
    }

    str[i++] = '\n';
    str[i++] = '\0';

}
