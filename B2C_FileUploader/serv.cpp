/*
Project Name        :            B2C_FileUplader_Server
Version             :            1.2
Author              :            Grant Liu
Project Start Date  :            2013/10/10
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
//#define ServIP          "127.0.0.1"

//Program Net Port settings.
#define ServPort        5555
#define MAX_CLIENTS     100
#define BufferSize      255
#define Len             255

//Get WSAData;
WORD wVersionRequested=MAKEWORD(2,2);
WSADATA wsaData;

/*Save muliti-thread infos.
  Handle:    array HClients.
  ThreadID:  array HClientsThreadID;
*/

int ClientsCount=0;
HANDLE HClients[MAX_CLIENTS]={0};
DWORD HClientsThreadID[MAX_CLIENTS]={0};
string tmp[MAX_CLIENTS]={""};

struct TThreadList
{
    int Num;
    char HelloBag[BufferSize];
} ThreadList[MAX_CLIENTS];

/*
Sockets:
       Self:    for init and get new connections.
       Recver:  each thread has one to get real infos.

RealReadSize:
       Each Socket read buffer for RealReadSize;

GreetBufs:the HEAD BUF between communication.
RBuf:     Buffers to read.
*/

SOCKET Self,Recver[MAX_CLIENTS];

int RealReadSize[MAX_CLIENTS];
char FileGreetBuf[BufferSize]= "SENDFILE";
char DirGreetBuf[BufferSize]="SENDDIR";
char CompleteBuf[BufferSize]="COMPLETE";
char Rbuf[MAX_CLIENTS][BufferSize];
string FilePath[MAX_CLIENTS]={""};

char HelloBag[MAX_CLIENTS][BufferSize]={""};
bool f[MAX_CLIENTS]={true};
FILE *FileStream[MAX_CLIENTS]={NULL};

//Every time the FileInfo is saved in this struct.
struct TFileInfo
{
    char FileName[BufferSize];
    char FilePath[BufferSize];
    char NakedPath[BufferSize];
    int  FileSize;
} FileInfo[MAX_CLIENTS];

struct TWorkMode
{
    int Mode; //1 is file;2 is directory;
    char FileName[BufferSize];
    char FilePath[BufferSize];
    char NakedPath[BufferSize];
};

struct sockaddr_in ServAddr,ClientAddr[MAX_CLIENTS];

int InitialWSA(void)
{
   if (WSAStartup(wVersionRequested,&wsaData)!=0)
        return WSAGetLastError();
   return 0;
}

int InitialSocket(void)
{
   Self=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if (Self==INVALID_SOCKET)
        return WSAGetLastError();
   return 0;
}

int BindServInfo(void)
{
   // ServAddr.sin_addr.S_un.S_addr=htonl(ServIP);
    ServAddr.sin_family=AF_INET;
    ServAddr.sin_port=htons(ServPort);
    ServAddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
    if(bind(Self,(sockaddr*)&ServAddr,sizeof(ServAddr))==SOCKET_ERROR)
       return WSAGetLastError();
    return 0;
}

int StartListen(void)
{
    if (listen(Self,MAX_CLIENTS)==SOCKET_ERROR)
        return WSAGetLastError();
    return 0;
}

void Logger(string Info)
{
   //TO LOG FAILURE INFORMATION.
   //FOR debug ONLY.
   /*
    FILE *f;
    fopen("Logs.txt","a");
    fputs(Info.c_str(),f);
    fputs("\n",f);
    fclose(f);
    */
}

DWORD WINAPI SocketIssues(LPVOID PIN)
{
  //The core function for each thread!!!
  //Nowa is nowa!!!!!!!
  int Nowa;
  Nowa=int(PIN);
   while (f[Nowa])
   {
     if (recv(Recver[Nowa],(char*)&Rbuf[Nowa],sizeof(Rbuf[Nowa]),0)<=0)
         break;
       if (strcmp(Rbuf[Nowa],FileGreetBuf)==0)
       {
          recv(Recver[Nowa],(char*)&FileInfo[Nowa],sizeof(FileInfo[Nowa]),0);
          system("cls");
          cout<<"============Recv Mode==============="<<endl;
          cout<<"Original File Name:"<<FileInfo[Nowa].FilePath<<endl;
          cout<<"Original File Size:"<<FileInfo[Nowa].FileSize<<" Bytes"<<endl;
          string tmp2(FileInfo[Nowa].NakedPath);
          FilePath[Nowa]=tmp[Nowa]+tmp2;

          //Recv Core..
          FileStream[Nowa]=fopen(FilePath[Nowa].c_str(),"wb");
          if (FileStream[Nowa]==NULL)
          {
                //string LoggInfo="File Create Failure:";
                //LoggInfo=LoggInfo+FilePath;
               // Logger(LoggInfo);
          }
          bool flager=true;
          int FileSizeSave=FileInfo[Nowa].FileSize;

          while (flager==true && FileInfo[Nowa].FileSize!=0)
            {
              if (FileInfo[Nowa].FileSize<=BufferSize)
                {
                  RealReadSize[Nowa]=recv(Recver[Nowa],Rbuf[Nowa],FileInfo[Nowa].FileSize,0);
                  fwrite(Rbuf[Nowa],1,RealReadSize[Nowa],FileStream[Nowa]);
                  FileInfo[Nowa].FileSize=0;
                  cout<<" 100% Completed."<<endl;
                }
              else
              {
                  RealReadSize[Nowa]=recv(Recver[Nowa],Rbuf[Nowa],BufferSize,0);
                  FileInfo[Nowa].FileSize=FileInfo[Nowa].FileSize-BufferSize;
                  fwrite(Rbuf[Nowa],1,RealReadSize[Nowa],FileStream[Nowa]);
                  //cout<<" "<<100*(FileSizeSave-FileInfo.FileSize)/FileSizeSave<<"%";
              }

              if (FileInfo[Nowa].FileSize==0)
              {
                   RealReadSize[Nowa]=recv(Recver[Nowa],Rbuf[Nowa],sizeof(CompleteBuf),0);
                   if (strcmp(Rbuf[Nowa],CompleteBuf)==0)
                    {
                     cout<<"Recv File complete..."<<endl;
                     flager=false;
                    }

               }
       }
  fclose(FileStream[Nowa]);
   } //File
   else if (strcmp(Rbuf[Nowa],DirGreetBuf)==0)
         {


          system("cls");
          cout<<"============Recv Mode==============="<<endl;


          recv(Recver[Nowa],(char*)&FileInfo[Nowa],sizeof(FileInfo[Nowa]),0);

          cout<<"Creating Original Directory:"<<FileInfo[Nowa].FilePath<<endl;
          //cout<<endl<<endl<<endl;
          //cout<<"Directory Naked Path:"<<FileInfo.NakedPath<<endl;
          //SleepEx(2000,true);

          string tmp2(FileInfo[Nowa].NakedPath);
          FilePath[Nowa]=tmp[Nowa]+tmp2;

         if (!CreateDirectory(FilePath[Nowa].c_str(),NULL))
          {
            if (GetLastError() != ERROR_ALREADY_EXISTS)
              {
                //cout<<"Create Failed..."<<endl;
                //cout<<FilePath[Nowa]<<endl;
                //cout<<"Fail Info:"<<GetLastError()<<endl;
                //SleepEx(500,true);
                char TmpCmd[]="md ";
                strcat(TmpCmd,FilePath[Nowa].c_str());
                system(TmpCmd);

                //string LoggInfo="Directory Create Failure:";
                //LoggInfo=LoggInfo+FilePath;
                //Logger(LoggInfo);
                //return 0;
              }
          }


          RealReadSize[Nowa]=recv(Recver[Nowa],Rbuf[Nowa],sizeof(CompleteBuf),0);
          if (strcmp(Rbuf[Nowa],CompleteBuf)==0)
                     cout<<"Created Directory complete..."<<endl;

         }//DIR
    //SleepEx(500,true);
   }
   cout<<"Client:"<<HelloBag[Nowa]<<" have DISCONNECTED...."<<endl;
   return 0;
}





int main()

{

  if (InitialWSA()!=0)
    {
      cout<<"Error:Initial WSA!"<<endl;
      return 1;
    }
  if (InitialSocket()!=0)
   {
      cout<<"Error:Initial Socket!"<<endl;
      return 2;
   }

   if (BindServInfo()!=0)
   {
    cout<<"Error:Bind Socket!"<<endl;
    return 3;
   }

   if (StartListen()!=0)
   {
       cout<<"Error:Start Listen!"<<endl;
       return 4;
   }
   int SizeClientAddr=sizeof(ClientAddr[1]);
   //阻塞式：一直等着ACCPET.........
   while (true)
   {
     ClientsCount++;
     Recver[ClientsCount]=accept(Self,(sockaddr*)&ClientAddr[ClientsCount],&SizeClientAddr);
     cout<<"Finded a Client Connected!"<<endl;
     recv(Recver[ClientsCount],(char*)&Rbuf[ClientsCount],sizeof(Rbuf[ClientsCount]),0);
     cout<<"Client Name:"<<Rbuf[ClientsCount]<<endl;

     strcpy(HelloBag[ClientsCount],Rbuf[ClientsCount]);
     tmp[ClientsCount]=HelloBag[ClientsCount];
     tmp[ClientsCount]="\\"+tmp[ClientsCount];

     f[ClientsCount]=true;
     //ThreadList[ClientsCount].HelloBag=HelloBag[ClientsCount];
     //ThreadList[ClientsCount].Num=ClientsCount;
     CreateDirectory(tmp[ClientsCount].c_str(),NULL);

     HClients[ClientsCount]=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)SocketIssues,(LPVOID)ClientsCount,0,&HClientsThreadID[ClientsCount]);

  }
  return 0;
}




