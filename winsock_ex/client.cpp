/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-09-16.42
 =============================================================*/
 //NO NEED TO BIND IN CLIENT!!!!!!!!!!!!!!!!!!!!!!!!!
#define SERV_PORT   5555
#define SERV_ADDR   127.0.0.1
#include <winsock2.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
    printf("Loading Necessary Library...\n");
    =MAKEWORD(2,2);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested,&wsaData)!=0)
       {
           printf("WSAStartup Failed!!!\n");
           return WSAGetLastError();
       }
    else
      printf("Loaded WSA Library successfully!\n");

    printf("Creating Sockets...\n");

    SOCKET s;

    s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    if (s==INVALID_SOCKET)
    {
        printf("Created Socket Failed!!!\n");
        return WSAGetLastError();
    }
    else
     printf("Created Socket successfully!\n");

    struct sockaddr_in Sadd;

    Sadd.sin_family=AF_INET;
    Sadd.sin_port=htons(SERV_PORT);

//    Sadd.sin_addr.S_un.S_addr=htonl("127.0.0.1");
      Sadd.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
   int ret;
   ret = connect(s, (sockaddr*)&Sadd, sizeof(Sadd));
   if (ret == SOCKET_ERROR)
   {
        printf("connect() failed!\n");
        closesocket(s);
        WSACleanup();
        return 0;
   }
  char sendMessage[256]="hello this is client message!";
  char Rbuf[256];
  int nRecv;

    while (1)
    {
      ret=send(s,(char*)&sendMessage, sizeof(sendMessage),0);
    if (ret == SOCKET_ERROR)
     {
        printf("send() failed!\n");
        printf("%d",WSAGetLastError());
        SleepEx(1000,true);
        //return 0;
    }
   else
        {
          printf("client info has been sent!\n");
          SleepEx(1000,true);
        }
         nRecv=recv(s,Rbuf,sizeof(Rbuf),0);
         if (nRecv==0) //客户端已经关闭连接
         printf("Client has closed the connection\n");
        printf("Get message from Serv::::%s\n",Rbuf);


    }
    WSACleanup;
    return 0;
}

