/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-10-17.48
 =============================================================*/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define LEN 1024
BOOL  DirectoryList(LPCSTR Path)
{
 WIN32_FIND_DATA FindData;
 HANDLE hError;
 char FilePathName[LEN];
 char FullPathName[LEN];
 strcpy(FilePathName, Path);
 strcat(FilePathName, "\\*.*");
 hError = FindFirstFile(FilePathName, &FindData);
 while(::FindNextFile(hError, &FindData))
 {
  if (strcmp(FindData.cFileName, ".") == 0
   || strcmp(FindData.cFileName, "..") == 0 )
  {
   continue;
 }
 wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);
if (FindData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
{
    printf("%s\n",FullPathName);
    SleepEx(1000,true);
}
  if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
  {
   DirectoryList(FullPathName);
  }



 }
 return 0;
}

int main()
{
 DirectoryList("d:");
 return 0;

}
