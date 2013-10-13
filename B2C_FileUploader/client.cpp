/*
Project Name        :            B2C_FileUplader_Client
Version             :            1.2
Author              :            Grant Liu
Project Start Date  :            2013/10/9
Project Finish Date :            2013/10/12
*/

#include <winsock2.h>
#include <string>
#include <stdio.h>
#include <io.h>
#include <windows.h>
#include <iostream>
using namespace std;

//#define STR_GREAT       "CLIENT REQUEST CONNECT"
//#define STR_FILE_SEND   "CLIENT REQUEST SEND"
//#define STR_BYE         "CLIENT REQUEST DISCONNCET"
#define ServIP          "192.168.173.1"
#define ServPort        5555
#define LEN             255
#define BufferSize      255



WORD wVersionRequested=MAKEWORD(2,2);
WSADATA wsaData;
SOCKET Sender;
HANDLE HSocketMainThread;
DWORD  SocketMainThreadID;
int Cmd,RealReadSize;
bool f=true;
char SendBuf[BufferSize];
char RootDir[BufferSize];

FILE *FileStream=NULL;

//Some Basic Greeting infos.
char FileGreetBuf[BufferSize] = "SENDFILE";
char DirGreetBuf[BufferSize]="SENDDIR";
char CompleteBuf[BufferSize]="COMPLETE";
char HelloBuf[BufferSize];

struct TFileInfo
{
    char FileName[BufferSize];
    char FilePath[BufferSize];
    char NakedPath[BufferSize];
    int  FileSize;
} FileInfo;

struct TWorkMode
{
    int Mode; //1 is file;2 is directory;
    char FileName[BufferSize];
    char FilePath[BufferSize];
    char NakedPath[BufferSize];
};

int TWMLen=sizeof(TWorkMode);

struct sockaddr_in ServAddr;

int InitialWSA(void)
{
   if (WSAStartup(wVersionRequested,&wsaData)!=0)
        return WSAGetLastError();
   return 0;
}

int InitialSocket(void)
{
   Sender=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if (Sender==INVALID_SOCKET)
        return WSAGetLastError();
   return 0;
}

int SetServInfo(void)
{
   // ServAddr.sin_addr.S_un.S_addr=htonl(ServIP);
    ServAddr.sin_family=AF_INET;
    ServAddr.sin_port=htons(ServPort);
    ServAddr.sin_addr.S_un.S_addr=inet_addr(ServIP);
}

int TryConnect(void)
{
    do
      {

      system("cls");
      cout<<"Trying to connect to Serv:"<<ServIP<<" @Port:"<<ServPort<<endl;
      SleepEx(1000,true);
      }
    while (connect(Sender,(sockaddr*)&ServAddr, sizeof(ServAddr))==SOCKET_ERROR);
    cout<<"Connect Serv successfully..."<<endl;
    return 0;
}



BOOL  DirectoryList(LPCSTR Path,string TDir)
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
    continue;
 wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);
  if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) ||
     (FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ||
     (FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ||
     (FindData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) ||
     (FindData.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) ||
     (FindData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED))
{
    //IS FILE!!!!
    struct TWorkMode *p;
    //Warning:Before use *p in struct.You MUST ALLOC MEMORY!
    p=(struct TWorkMode *)malloc(TWMLen);
   // memset(p,0,sizeof(*p));
    p->Mode=1;
    strcpy(p->FileName,FindData.cFileName);
    strcpy(p->FilePath,FullPathName);
    string tmp="";
    tmp=TDir;
    tmp=tmp+FindData.cFileName;
    for (int i=0;i<tmp.length();i++)
        p->NakedPath[i]=tmp.c_str()[i];

    while (PostThreadMessage(SocketMainThreadID,0,int(p),0)==false)
    {
        SleepEx(10,true);
    }


}
  if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
  {
   //NEXT DIRECTORY!
    struct TWorkMode *p;
   // memset(p,0,sizeof(TWorkMode));
    p=(struct TWorkMode *)malloc(TWMLen);
    p->Mode=2;
    strcpy(p->FileName,FindData.cFileName);
    strcpy(p->FilePath,FullPathName);
    string tmp2="";
    tmp2=TDir;
    tmp2=tmp2+FindData.cFileName;
    tmp2=tmp2+"\\\\";
    for (int i=0;i<tmp2.length();i++)
      p->NakedPath[i]=tmp2.c_str()[i];

    while (PostThreadMessage(SocketMainThreadID,0,int(p),0)==false)
    {
        SleepEx(10,true);
    }

   DirectoryList(FullPathName,tmp2);
  }



 }
 return 0;
}

void GenerateHelloBuf(void)
{
  gethostname(HelloBuf,sizeof(HelloBuf));
}
void SocketMain()

{

  if (InitialWSA()!=0)
    {
      cout<<"Error:Initial WSA!"<<endl;
      //return 1;
    }
  if (InitialSocket()!=0)
   {
      cout<<"Error:Initial Socket!"<<endl;
      //return 2;
   }
   SetServInfo();

   if (TryConnect()!=0)
   {
    cout<<"Error:Connect to Serv!"<<endl;
    //return 3;
   }

  GenerateHelloBuf();
  send(Sender,HelloBuf,sizeof(HelloBuf),0);

  cout<<"============Send Mode==============="<<endl;
  MSG Msg1;

  while (f)
   {
        if (GetMessage(&Msg1,NULL,0,0))
           {
           //GetNewmessage
           memset(&FileInfo,0,sizeof(FileInfo));

           system("cls");
           cout<<"============Send Mode==============="<<endl;
           struct TWorkMode *p;
           p=(TWorkMode*)(Msg1.wParam);
           cout<<"[Now Processing]"<<endl;
           cout<<p->NakedPath<<endl;

           if (p->Mode==1)
             {
               strcpy(FileInfo.FileName,p->FileName);
               strcpy(FileInfo.FilePath,p->FilePath);
               strcpy(FileInfo.NakedPath,p->NakedPath);
               delete(p);
               FileStream=fopen(FileInfo.FilePath,"rb");
               if (FileStream==NULL)
                 {
                  fclose(FileStream);
                  continue;
                 }
                FileInfo.FileSize=filelength(fileno(FileStream));
                //Now Greet&Send File Info.
                send(Sender,(char*)&FileGreetBuf,sizeof(FileGreetBuf),0);
                send(Sender,(char*)&FileInfo,sizeof(FileInfo),0);

                //Send Core.
                while (!feof(FileStream)&&(FileInfo.FileSize!=0))
                  {
                     //fread(SAVE_TO_BUF,GROUPS,GROUP_SIZE,FILESTREAM)

                     if (FileInfo.FileSize<=BufferSize)
                      {
                       RealReadSize=fread(SendBuf,1,FileInfo.FileSize,FileStream);
                       FileInfo.FileSize=0;
                      }
                     else
                      {
                        RealReadSize=fread(SendBuf,1,BufferSize,FileStream);
                        FileInfo.FileSize=FileInfo.FileSize-BufferSize;
                      }
                      send(Sender,SendBuf,RealReadSize,0);
                  }
                 send(Sender,CompleteBuf,sizeof(CompleteBuf),0);
             fclose(FileStream);
           } //Mode=1

           else if (p->Mode==2)
           {
               //Directory!!!!!
               strcpy(FileInfo.FileName,p->FileName);
               strcpy(FileInfo.FilePath,p->FilePath);
               strcpy(FileInfo.NakedPath,p->NakedPath);
               delete(p);
               send(Sender,(char*)&DirGreetBuf,sizeof(DirGreetBuf),0);
               send(Sender,(char*)&FileInfo,sizeof(FileInfo),0);
               send(Sender,CompleteBuf,sizeof(CompleteBuf),0);
           }
   }  //GetMessage
   }  //while

}  //Socket

int main()
{
   HSocketMainThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)SocketMain,NULL,0,&SocketMainThreadID);
   strcpy(RootDir,"d:\\’’∆¨ºØ");
   string TDir(RootDir);
   TDir=TDir.substr(strlen(RootDir),LEN);
   TDir=TDir+"\\";
   DirectoryList(RootDir,TDir);
   cout<<"Search COMPLETE..."<<endl;
   while(1)
   {

   }
}
