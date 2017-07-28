//main.c主要完成对整个程序的调度,

//具体实现解析参数,储存选项参数,判断参数为目录或是文件,并且进行下一步的传参

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<linux/limits.h>
#include<dirent.h>
#include<time.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define MAXLINE 80

int  line_left = MAXLINE;

int  file_max_name;

void _error(const char *err_string,int line);                 //错误判断函数

void list_file_single(char *name);                            //没有文件/目录名ls

void list_dir_pre(int flag_option,char *path);                //目录信息ls的准备环节,进行目录信息的获取,并且排序;

void list_file(int flag_option,char *path);                   //文件信息ls的准备,进行不同选项的选择

void list_file_information(struct stat buffer,char *name);                   //显示文件详细信息

int main(int argc,char **argv)
{
    char path[PATH_MAX + 1];                                  //表示获取到的文件名

    char option[5];                                           //存储ls命令的选项

    int flag_option;                                          //用来进行信息打印时的传参

    struct stat buffer;                                       //进行判断文件/目录名是否合法

    int i, j, t, num;

    j = 0;

    num = 0;

    //进行命令行参数的解析,并存入数组option中,方便之后进行ls的传参
    for(i = 1;i < argc;i++)
    {
        if(argv[i][0] == '-')
        {
            for(t = 1;t < strlen(argv[i]);t++)
                option[j++] = argv[i][t];
            num++;
        }
    }

    //分析存储在option中的参数,a=1,l=2,R=4 获取权数,为之后的list函数做准备
    flag_option = 0;
    for(i = 0;i < 5;i++)
    {
        if(option[i] == 'a')
            flag_option += 1;
        else if(option[i] == 'l')
            flag_option += 2;
        else if(option[i] == 'R')
            flag_option += 4;
    }
    option[i] = '\0';

    //获取文件名/目录名

    //如果没有文件/目录名参数,那么就以本目录为参数,完成后即可return结束
    if(num + 1 == argc)
    {
        strcpy(path,"./");
        path[2] = '\0';
        list_dir_pre(flag_option,path);
        return 0;
    }

    //如果有自己的参数,那么便进行参数的分析,因为即使没有任何参数也可以正常运行,
    i = 1;
    do
    {
        if(argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else
        {
            strcpy(path,argv[i]);
            if(stat(path,&buffer) == -1)
            {
                _error("stat",__LINE__);
            }
            if(S_ISDIR(buffer.st_mode))       //判断path为一个目录,则为其补上'/'
            {
                if(path[strlen(argv[i])-1] != '/')
                {
                    path[strlen(argv[i])] = '/';
                    path[strlen(argv[i])+1] = '\0';
                }
                else
                    path[strlen(argv[i])] = '\0';
                list_dir_pre(flag_option,path);
                i++;
            }
            else
            {
                list_file(flag_option,path);
                i++;
            }

        }
    
    }while (i < argc);

    return 0;
}

void list_dir_pre(int flag_option,char *path)
{
   DIR *dir;
   struct dirent *ptr;
   int count = 0;
   char filename[300][PATH_MAX+1];
   char temp[PATH_MAX+1];

   //获取该目录下文件/目录的数量以及最长文件名
   dir = opendir(path);
   if(dir == NULL)
   {
      _error("opendir",__LINE__);
   }

   while((ptr = readdir(dir)) != NULL)
   {
      if(strlen(ptr->d_name) > file_max_name)
      {
         file_max_name = strlen(ptr->d_name);   
      }
      count++;
   }
   closedir(dir);
   
   if(count > 300)
   {
      printf("Error!It can't display too many files!\n");
      exit(0);
   }

   //获取目录中的所有文件名并存储在filaname二维数组中
   int i,j,length;

   length = strlen(path);
   dir = opendir(path);
   for(i = 0;i < count;i++)
   {
      ptr = readdir(dir);
      if(ptr == NULL)
      break;
      strncpy(filename[i],path,length);
      strcat(filename[i],ptr->d_name);
      filename[i][strlen(filename[i])] = '\0';
   }

   //对获取到的目录内容进行排序
   while(count--)
   {
      for(i = 0;i < count;i++)
      {
         if(strcmp(filename[i],filename[i+1]) > 0)
         {
            strcpy(temp,filename[i]);
            temp[strlen(filename[i])] = '\0';
            strcpy(filename[i],filename[i+1]);
            filename[i][strlen(filename[i+1])] = '\0';
            strcpy(filename[i+1],temp);
            filename[i+1][strlen(temp)] = '\0';
         }
      }
   }

   //按顺序输出所有的文件
   for(i = 0;i < count;i++)
      list_file(flag_option,filename[i]);

   closedir(dir);
}

void list_file(int flag_option,char *filename)
{
   int i,j;
   struct stat   buffer;
   char  name[NAME_MAX+1];

   //从filename中解析name出来
   for(i = 0,j = 0;i < strlen(filename);i++)
   {
      if(filename[i] == '/')
      {
         j = 0;
         continue;
      }
      name[j++] = filename[i];
   }
   name[j] = '\0';

   //使用lstat方便处理连接文件
   if(lstat(filename,&buffer) == -1)
   {
      _error("lstat",__LINE__);
   }

   switch(flag_option)
   {
      case 0:                                          //无
         if(name[0] != '.')
            list_file_single(name);
         break;
      
      case 1:                                          //-a
         list_file_single(name);
         break;
      
      case 2:                                          //-l
         if(name[0] != '.')
         {
            list_file_information(buffer,name);
            printf("  %-s\n",name);
         }
         break;
      
      case 3:                                          //-al
         list_file_information(buffer,name);
         printf("  %-s\n",name);
         break;

      case 4:                                          //-R

      case 5:                                          //-aR

      case 6:                                          //-lR

      case 7:                                          //-alR

      default:
         break;
   }
}

void list_file_information(struct stat buffer, char *name)
{
   char buffer_time[32];
   struct passwd *psd;                                                         //用于获取用户名
   struct group *grp;                                                          //用于获取用户组名

   //获取并打印文件的类型
   if(S_ISLNK(buffer.st_mode))
      printf("l");
   else if(S_ISREG(buffer.st_mode))
      printf("-");
   else if(S_ISDIR(buffer.st_mode))
      printf("d");
   else if(S_ISCHR(buffer.st_mode))
      printf("c");
   else if(S_ISBLK(buffer.st_mode))
      printf("b");
   else if(S_ISFIFO(buffer.st_mode))
      printf("f");
   else if(S_ISSOCK(buffer.st_mode))
      printf("s");

   //获取并打印文件所有者权限
   if(buffer.st_mode & S_IRUSR)
      printf("r");
   else
      printf("-");
   if(buffer.st_mode & S_IWUSR)
      printf("w");
   else
      printf("-");
   if(buffer.st_mode & S_IXUSR)
      printf("x");
   else
      printf("-");

   //获取并打印文件用户组权限
   if(buffer.st_mode & S_IRGRP)
      printf("r");
   else
      printf("-");
   if(buffer.st_mode & S_IWGRP)
      printf("w");
   else
      printf("-");
   if(buffer.st_mode & S_IXGRP)
      printf("x");
   else
      printf("-");

   //获取并打印其他用户的权限
   if(buffer.st_mode & S_IROTH)
      printf("r");
   else
      printf("-");
   if(buffer.st_mode & S_IWOTH)
      printf("w");
   else
      printf("-");
   if(buffer.st_mode & S_IXOTH)
      printf("x");
   else
      printf("-");

   printf("   ");

   //根据uid与gid获取文件拥有者的用户及用户组
   psd = getpwuid(buffer.st_uid);
   grp = getgrgid(buffer.st_gid);
   printf("%4d  ",buffer.st_nlink);
   printf("%-8s",psd->pw_name);
   printf("%-8s",grp->gr_name);

   printf("%6d",buffer.st_size);       //打印文件的大小
   strcpy(buffer_time,ctime(&buffer.st_mtime));
   buffer_time[strlen(buffer_time) - 1] = '\0';
   printf("  %s",buffer_time);

}

void list_file_single(char *name)
{
   int i,length;

   //如果不足以打印一个最大文件名就换行
   if(line_left < file_max_name)
   {
      printf("\n");
      line_left = MAXLINE;
   }

   length = strlen(name);
   length = file_max_name - length;
   printf("%-s",name);
   for(i = 0;i < length;i++)
   {
      printf(" ");
   }

   line_left -= (file_max_name+2);
}

void _error(const char *err_string,int line)
{
    printf("Error line :%d\n",line);
    perror(err_string);
    exit(0);
}
