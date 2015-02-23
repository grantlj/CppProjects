/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-09-14.20
 =============================================================*/


//#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <winsock2.h>

#define SERVER_PORT 5208 //�����˿�

int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int ret, nLeft, length;
    SOCKET sListen, sServer; //�����׽��֣������׽���
    struct sockaddr_in saServer, saClient; //��ַ��Ϣ
    char *ptr;//���ڱ�����Ϣ��ָ��
    //WinSock��ʼ��
    wVersionRequested=MAKEWORD(2, 2); //ϣ��ʹ�õ�WinSock DLL �İ汾
    ret=WSAStartup(wVersionRequested, &wsaData);
    if(ret!=0)
    {
        printf("WSAStartup() failed!\n");
        return 0;
    }
    //����Socket,ʹ��TCPЭ��
    s=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s==INVALID_SOCKET)
    {
        WSACleanup();
        printf("socket() faild!\n");
        return 0;
    }
    //�������ص�ַ��Ϣ
    saServer.sin_family = AF_INET; //��ַ����
    saServer.sin_port = htons(SERVER_PORT); //ע��ת��Ϊ�����ֽ���
    saServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //ʹ��INADDR_ANY ָʾ�����ַ

    //��
    ret = bind(sListen, (struct sockaddr *)&saServer, sizeof(saServer));
    if (ret == SOCKET_ERROR)
    {
        printf("bind() faild! code:%d\n", WSAGetLastError());
        closesocket(sListen); //�ر��׽���
        WSACleanup();
        return 0;
    }

    //������������
    ret = listen(sListen, 5);
    if (ret == SOCKET_ERROR)
    {
        printf("listen() faild! code:%d\n", WSAGetLastError());
        closesocket(sListen); //�ر��׽���
        return 0;
    }

    printf("Waiting for client connecting!\n");
    printf("Tips: Ctrl+c to quit!\n");
    //�����ȴ����ܿͻ�������
 while(1)//ѭ�������ͻ��ˣ���Զ��ֹͣ�����ԣ��ڱ���Ŀ�У�����û����������
 {
  length = sizeof(saClient);
  sServer = accept(sListen, (struct sockaddr *)&saClient, &length);
  if (sServer == INVALID_SOCKET)
  {
   printf("accept() faild! code:%d\n", WSAGetLastError());
   closesocket(sListen); //�ر��׽���
   WSACleanup();
   return 0;
  }
  char receiveMessage[5000];
   nLeft = sizeof(receiveMessage);
  ptr = (char *)&receiveMessage;
  while(nLeft>0)
  {
   //��������
   ret = recv(sServer, ptr, 5000, 0);
   if (ret == SOCKET_ERROR)
   {
    printf("recv() failed!\n");
    return 0;
   }
   if (ret == 0) //�ͻ����Ѿ��ر�����
   {
    printf("Client has closed the connection\n");
    break;
   }
   nLeft -= ret;
   ptr += ret;
  }
    printf("receive message:%s\n", receiveMessage);//��ӡ���ǽ��յ�����Ϣ��

 }
  //  closesocket(sListen);
  //  closesocket(sServer);
  //  WSACleanup();
  return 0;
}
