/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-23-15.32
 =============================================================*/
#include <stdio.h>
int main(int argc,char *argv[])
{
  printf("%s\n",argv[0]);
  int i;
  for (i=1;i<argc;i++)
    printf("%s\n",argv[i]);
  return 0;
}
