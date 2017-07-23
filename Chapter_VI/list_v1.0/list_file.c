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
   if(lstat(name,&buffer) == -1)
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
