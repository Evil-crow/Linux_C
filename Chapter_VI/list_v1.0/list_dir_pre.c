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

   while(ptr = readdir(dir) != NULL)
   {
      if(ptr->d_name > file_max_name)
      {
         file_max_name = ptr->d_name;   
      }
      count++;
   }
   close(dir);
   
   if(count > 300)
   {
      printf("Error!It can't display too many files!\n");
      exit(0);
   }

   //获取目录中的所有文件名并存储在filaname二维数组中
   int i,j;

   length = strlen(path);
   dir = open(path);
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
         if(strcmp(filename[i] > filname[i+1]))
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

   close(dir);
}
