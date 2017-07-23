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
   psd = getpwuid(buffer.st_mode);
   grp = getgrgid(buffer.st_mode);
   printf("%4d  ",buffer.st_link);
   printf("%-8s",psd->pw_name);
   printf("%-8s".grp->gr_name);

   printf("%6d",buffer.st_size);       //打印文件的大小
   strcpy(buffer.time,ctime(&buffer.st_time));
   buffer_time[strlen(buffer_time) - 1] = '\0';
   printf("  %s",buffer_time);

}
