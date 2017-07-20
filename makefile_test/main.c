#include"stdio.h"
#include"string.h"
char *result(char *,int );
int main(void)
{
   char str[1000];
   
   fgets(str,1000,stdin);
   int length = strlen(str);
   str[length] = '\0';
   result(str,length);

   return 0;
}
