/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-09-14.44
 =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define SERVER_PORT 5208 //侦听端口
int main()
{
   WORD wVersionRequested;
   WSADATA wsaData;
   int ret;
   SOCKET sClient; //连接套接字
   struct sockaddr_in saServer; //地址信息
   char *ptr;
   BOOL fSuccess = TRUE;
   //WinSock初始化
   wVersionRequested = MAKEWORD(2, 2); //希望使用的WinSock DLL的版本
   ret = WSAStartup(wVersionRequested, &wsaData);
   if(ret!=0)
   {
        printf("WSAStartup() failed!\n");
        return 0;
   }
   //确认WinSock DLL支持版本2.2
   if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
   {
        WSACleanup();
        printf("Invalid WinSock version!\n");
        return 0;
   }
   //创建Socket,使用TCP协议
   sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (sClient == INVALID_SOCKET)
   {
        WSACleanup();
        printf("socket() failed!\n");
        return 0;
   }
   //构建服务器地址信息
   saServer.sin_family = AF_INET; //地址家族
   saServer.sin_port = htons(SERVER_PORT); //注意转化为网络节序
   saServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
   //连接服务器
   ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
   if (ret == SOCKET_ERROR)
   {
        printf("connect() failed!\n");
        closesocket(sClient); //关闭套接字
        WSACleanup();
        return 0;
   }


   char sendMessage[]="hello this is client message!";
   ret = send (sClient, (char *)&sendMessage, sizeof(sendMessage), 0);
   if (ret == SOCKET_ERROR)
   {
        printf("send() failed!\n");
   }
   else
        printf("client info has been sent!");
   closesocket(sClient); //关闭套接字
   WSACleanup();
   return 0;
}
