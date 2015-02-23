/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-09-14.44
 =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define SERVER_PORT 5208 //�����˿�
int main()
{
   WORD wVersionRequested;
   WSADATA wsaData;
   int ret;
   SOCKET sClient; //�����׽���
   struct sockaddr_in saServer; //��ַ��Ϣ
   char *ptr;
   BOOL fSuccess = TRUE;
   //WinSock��ʼ��
   wVersionRequested = MAKEWORD(2, 2); //ϣ��ʹ�õ�WinSock DLL�İ汾
   ret = WSAStartup(wVersionRequested, &wsaData);
   if(ret!=0)
   {
        printf("WSAStartup() failed!\n");
        return 0;
   }
   //ȷ��WinSock DLL֧�ְ汾2.2
   if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
   {
        WSACleanup();
        printf("Invalid WinSock version!\n");
        return 0;
   }
   //����Socket,ʹ��TCPЭ��
   sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (sClient == INVALID_SOCKET)
   {
        WSACleanup();
        printf("socket() failed!\n");
        return 0;
   }
   //������������ַ��Ϣ
   saServer.sin_family = AF_INET; //��ַ����
   saServer.sin_port = htons(SERVER_PORT); //ע��ת��Ϊ�������
   saServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
   //���ӷ�����
   ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(saServer));
   if (ret == SOCKET_ERROR)
   {
        printf("connect() failed!\n");
        closesocket(sClient); //�ر��׽���
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
   closesocket(sClient); //�ر��׽���
   WSACleanup();
   return 0;
}
