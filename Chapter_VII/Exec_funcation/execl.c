#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char **argv,char **envi)
{
   pid_t pid;
   printf("Exec start!\n");
   pid = fork( );
   if(pid == -1)
   {
      printf("Error!");
      exit(0);
   }
   else if(pid == 0)
   {
      printf("I am child process !\n");
      printf("my pid is %d,my parent pid is %d\n",getpid( ),getppid( ));
      execve("program",argv,envi);
      printf("This sentence won't be print!\n");
      _exit(0);
   }
   else
   {
      sleep(2);
      printf("This is parent process!\n");
   }

   return 0;
}
