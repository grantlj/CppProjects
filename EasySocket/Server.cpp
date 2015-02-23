/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-09-14.20
 =============================================================*/


//#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <winsock2.h>

#define SERVER_PORT 5208 //侦听端口

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int ret, nLeft, length;
    SOCKET sListen, sServer; //侦听套接字，连接套接字
    struct sockaddr_in saServer, saClient; //地址信息
    char *ptr;//用于遍历信息的指针
    //WinSock初始化
    wVersionRequested=MAKEWORD(2, 2); //希望使用的WinSock DLL 的版本
    ret=WSAStartup(wVersionRequested, &wsaData);
    if(ret!=0)
    {
        printf("WSAStartup() failed!\n");
        return 0;
    }
    //创建Socket,使用TCP协议
    s=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s==INVALID_SOCKET)
    {
        WSACleanup();
        printf("socket() faild!\n");
        return 0;
    }
    //构建本地地址信息
    saServer.sin_family = AF_INET; //地址家族
    saServer.sin_port = htons(SERVER_PORT); //注意转化为网络字节序
    saServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //使用INADDR_ANY 指示任意地址

    //绑定
    ret = bind(sListen, (struct sockaddr *)&saServer, sizeof(saServer));
    if (ret == SOCKET_ERROR)
    {
        printf("bind() faild! code:%d\n", WSAGetLastError());
        closesocket(sListen); //关闭套接字
        WSACleanup();
        return 0;
    }

    //侦听连接请求
    ret = listen(sListen, 5);
    if (ret == SOCKET_ERROR)
    {
        printf("listen() faild! code:%d\n", WSAGetLastError());
        closesocket(sListen); //关闭套接字
        return 0;
    }

    printf("Waiting for client connecting!\n");
    printf("Tips: Ctrl+c to quit!\n");
    //阻塞等待接受客户端连接
 while(1)//循环监听客户端，永远不停止，所以，在本项目中，我们没有心跳包。
 {
  length = sizeof(saClient);
  sServer = accept(sListen, (struct sockaddr *)&saClient, &length);
  if (sServer == INVALID_SOCKET)
  {
   printf("accept() faild! code:%d\n", WSAGetLastError());
   closesocket(sListen); //关闭套接字
   WSACleanup();
   return 0;
  }
  char receiveMessage[5000];
   nLeft = sizeof(receiveMessage);
  ptr = (char *)&receiveMessage;
  while(nLeft>0)
  {
   //接收数据
   ret = recv(sServer, ptr, 5000, 0);
   if (ret == SOCKET_ERROR)
   {
    printf("recv() failed!\n");
    return 0;
   }
   if (ret == 0) //客户端已经关闭连接
   {
    printf("Client has closed the connection\n");
    break;
   }
   nLeft -= ret;
   ptr += ret;
  }
    printf("receive message:%s\n", receiveMessage);//打印我们接收到的消息。

 }
  //  closesocket(sListen);
  //  closesocket(sServer);
  //  WSACleanup();
  return 0;
}
