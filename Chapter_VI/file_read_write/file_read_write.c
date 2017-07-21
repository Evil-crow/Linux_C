#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

void _error(const char *,int );

int file_read(int );

int file_write(int );

int main(int argc,char **argv)
{
   int fd;

   if(fd = open(argv[1],O_CREAT|O_EXCL|O_TRUNC,0644) < 0)
   {
      _error("open",__LINE__);
      exit(0);
   }
   fd = file_write(fd);
   fd = file_read(fd);

   if(lseek(fd,10,SEEK_END) == -1)
      _error("lseek",__LINE__);
   if(write(fd,"Hello World!",13) < 13)
      _error("write",__LINE__);

   file_read(fd);
   close(fd);

   return 0;
}

void _error(const char *error,int line)
{
   printf("Error!\n");
   printf("Error:%s    %d\n",strerror(errno),line);
   
   exit(0);
}

int file_write(int fd)
{
   char str[1000];
   
   gets(str);
   int length = strlen(str);
   str[length] = '\0';
   if(write(fd,str,length) != length)
   {
      _error("write",__LINE__);
      exit(0);
   }
   else
   {
      printf("Write data to the file successfully!\n");
      return fd;
   }

}

int file_read(int fd)
{
   char str[1000];
   int length;

   if (lseek(fd,0,SEEK_END) == -1){
      _error("lseek",__LINE__);
   }
   if ((length = lseek(fd,0,SEEK_CUR)) == -1){
      _error("lseek",__LINE__);
   }
   if ((lseek(fd,0,SEEK_SET)) == -1){
      _error("lseek",__LINE__);
   }

   printf("The legth is %d\n",length);

   if(read(fd,str,length) == -1)
      _error("read",__LINE__);
   else
      printf("Read data from the file successfully!\n");
   printf("%s\n",str);

   return fd;
}
