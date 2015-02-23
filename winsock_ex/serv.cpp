/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-09-15.32
 =============================================================*/
/*
======================NOTES=====================================
======================WSAData===================================

typedef struct WSAData {
WORD                    wVersion;
WORD                    wHighVersion;
char   szDescription[WSADESCRIPTION_LEN+1];
char    szSystemStatus[WSASYS_STATUS_LEN+1];
unsigned short          iMaxSockets;
unsigned short          iMaxUdpDg;
char FAR *              lpVendorInfo;
} WSADATA, FAR * LPWSADATA;

================Param of Socket Structure=======================
af ���׽���Ҫʹ�õ�Э���ַ�壬�ó���AF_INET��ʾʹ��IP��ַ

type�������׽��ֵ�Э������,ʹ�� SOCK_STREAM,SOCK_DGRAM,SOCK_RAW

protocol��˵���׽���ʹ�õ��ض�Э�� IPPROTO_TCP IPPROTO_UDP IPPROTO_RAW
//===============================================================

===============Bind Function=====================================
int bind��
   SOCKET s��
   const struct sockaddr FAR* name��
   int namelen
 ����

s��δ���׽ӿڵľ��  (��һ��������)
name����ָ��Э���йصĵ�ַ�ṹָ��,��Winsock��ʹ�� sockaddr_in�ṹ ָ��IP��ַ�Ͷ˿���Ϣ
namelen����ַ����(name)�ĳ���,��sizeof��Sadd��
                  ���


==============Socket_addr Structure========================
Struct sockaddr_in  {short sin_family;
                     u_short sin_port;
                     struct in_addr sin_addr;
                     char  sin_zero[8];//����,��0���
                    }


============= Function===============================
int listen��
   SOCKET s��
   int backlog��
 ����
s���׽ӿڵľ�� (֮ǰ�Ѿ�����)
Backlog ���ȴ����ӵ������г���
����дΪSOMAXCONN�²�����ṩ�߽����׽�������Ϊ������ֵ��
 eg�� listen(s, 2��
�����������������������2��
����3̨�ͻ���ͬʱ������������
����������Ŀͻ��˽��յ���������ͼ���ܾ����Ĵ������ 10061

===============Accpet Function=========================
=======================================================
SOCKET accept��
   SOCKET s��
   struct sockaddr* addr,
   int*addrlen
 ����
s���׽��־��    s
addr��ָ��һ����������ָ�루ָ��sockaddr_in�ṹ��ָ�룩��
��ȡ�Է��ĵ�ַ��Ϣ������ĳ�ͻ�������������ʱ����ÿͻ��˵�IP��ַ���˿���Ϣ��
addrlen ��ָ���ַ���ȵ�ָ��
    ָ��addr��ָ�ռ��С��
Ҳ���ڷ��ص�ַʵ�ʳ��ȣ����addr��addrlenΪNULL����û��Զ�̵�ַ��Ϣ����

======================Send Function=====================
int send ��
   SOCKET s��
   const char  FAR* buf��
   int len,
   int flags
 ����
s���������׽ӿ� ���   cli (���Ͷ��󣡣�����������
buf��ָ��һ������������������Ҫ��/��������) Sbuf
len������������   sizeof ( Sbuf )
flags��ָ�����÷�ʽ��ͨ������Ϊ0
�޴�:���ط���/���յ��ֽ��� isend       �д�:����SOCKET_ERROR

=====================Recv Function=====================
int recv(
 SOCKET s��
   const char  FAR* buf��
   int len,
   int flags
 );
s���������׽ӿ� ���  cli
buf��ָ��һ������������������Ҫ��/�������ݣ�Rbuf
len������������ sizeof ( Rbuf )
flags��ָ�����÷�ʽ��ͨ������Ϊ0



*/

#define SERV_PORT   5555
//#define SERV_ADDR   127.0.0.1
#define MAX_CLIENTS 100
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
using namespace std;
int main()
{
    //===========================================================
    //===========================================================
    //Load Necessary Library;
    printf("Loading Necessary Library...\n");
    //Generate WinSock Version.
    //HI: Vice Version Info.
    //LO: Main Version Info.
    WORD wVersionRequested=MAKEWORD(2,2);
    //WSADATA is a structure to SAVE INITIAL INFORMATION!!!!
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested,&wsaData)!=0)
       {
           //INITIAL FAILED!!!!
           printf("WSAStartup Failed!!!\n");
           return WSAGetLastError();
       }
    else
      printf("Loaded WSA Library successfully!\n");

    printf("Creating Sockets...\n");

    //===========================================================
    //===========================================================
    //Create Sockets!!!
    SOCKET s;
    //Create s as INTERNET TCP Service!!!!!!

    s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    //AF_INET: Internet Standard;
    //SOCKET_STREAM: TCP;
    //IPPROTO_TCP: TCP standard PROTOL!

    if (s==INVALID_SOCKET)
    {
        printf("Created Socket Failed!!!\n");
        return WSAGetLastError();
    }
    else
       printf("Created Socket successfully!\n");

    //===========================================================
    //===========================================================
    //Bind socket to THIS PC ITSELF!!!
    printf("Binding Socket to local IP...\n");

    struct sockaddr_in Sadd;

    Sadd.sin_family=AF_INET;
    Sadd.sin_port=htons(5555); //if it is 0 then random by system!!!

    //INADDR_ANY: means IGNORE PC'S REAL IP!!!!!ANY IS OK!!!!!
    //Bind IP INFO(Sadd) to Socket(s)!!!!!!!!!!!!!!!!!!!!!!!!!!

    Sadd.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
   // Sadd.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    if( bind(s,(sockaddr*)&Sadd,sizeof(Sadd))==SOCKET_ERROR)
        {
            printf("Bind Socket to IP Failed!!!\n");
            return WSAGetLastError();
        }
    else
        printf("Bind Socket to IP successfully!\n");

    //==================================================
    //==================================================
    //Start Listening....
    printf("Strating Listening...\n");
    if (listen(s,MAX_CLIENTS)==SOCKET_ERROR)
    {
        printf("Start listening failed!!!\n");
        return WSAGetLastError();
    }
    else
        printf("Start listening successfully!\n");



    //=================================================
    //=================================================
    //Start Accept Clients Request!
    struct sockaddr_in clientadd;
    int addLen=sizeof(clientadd);

    SOCKET cli;
    char Rbuf[256];
    memset(Rbuf,0,sizeof(Rbuf));
    int nRecv;
    cli=accept(s,(sockaddr*)&clientadd,&addLen);
    while (true)
      {
        // printf("in!\n");
         //By Exp: ����ʽ��������������

        /*
        } if (cli==INVALID_SOCKET)
         {
             printf("Accepted Client failed!\n");
             continue;
         }
         else
         {*/

             cout<<"Receive a new connection from IP:"<<inet_ntoa(clientadd.sin_addr)<<" & Port is:"<<
             ntohs(clientadd.sin_port)<<endl;

             nRecv=recv(cli,Rbuf,sizeof(Rbuf),0);

             if (nRecv==0) //�ͻ����Ѿ��ر�����
                printf("Client has closed the connection\n");

             if (nRecv=SOCKET_ERROR)
               {
                 printf("recv failed.\n");
                 printf("Get message from client::::%s",Rbuf);
                //continue;
               }
            else
                printf("Get message from client:%s",Rbuf);

             //Now Do Send!!!!!!
             int  isend;
             char  Sbuf[] = "Hello client! I am server !!";
             isend=send(cli,Sbuf,sizeof(Sbuf),0);
             if (isend==SOCKET_ERROR)
             {
                 printf("Send Message to Client failed...\n");
                 printf("Error Code:%d\n",WSAGetLastError());
                 continue;
             }
             else
                printf("Message [%s] sended successfully.\n",Sbuf);

             SleepEx(1000,true);
         //}
         //closesocket(cli);
      }
 closesocket(s);
 WSACleanup();
 return 0;

}
