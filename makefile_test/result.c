#include"string.h"
#include"stdio.h"
void result(char *str,int length)
{
   char ptr[1000];
   int t;

   for(t = 0;t < length;t++)
   {
      ptr[t] = str[length-t-1];
   }

   printf("%s\n",ptr);
}
