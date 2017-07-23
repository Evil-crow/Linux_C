void list_file_single(char *name)
{
   int i,length;

   //如果不足以打印一个最大文件名就换行
   if(line_left < file_max_name)
   {
      pritnf("\n");
      line_left = MAXLINE;
   }

   length = strlen(name);
   length = file_max_name - length;
   for(i = 0;i < file_max_name;i++)
   {
      printf(" ");
   }

   line_left -= file_max_name+2;
}
