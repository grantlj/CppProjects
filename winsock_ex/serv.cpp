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
af ：套接字要使用的协议地址族，用常量AF_INET表示使用IP地址

type：描述套接字的协议类型,使用 SOCK_STREAM,SOCK_DGRAM,SOCK_RAW

protocol：说明套接字使用的特定协议 IPPROTO_TCP IPPROTO_UDP IPPROTO_RAW
//===============================================================

===============Bind Function=====================================
int bind（
   SOCKET s，
   const struct sockaddr FAR* name，
   int namelen
 ）；

s：未绑定套接口的句柄  (上一步创建的)
name：与指定协议有关的地址结构指针,在Winsock中使用 sockaddr_in结构 指定IP地址和端口信息
namelen：地址参数(name)的长度,用sizeof（Sadd）
                  获得


==============Socket_addr Structure========================
Struct sockaddr_in  {short sin_family;
                     u_short sin_port;
                     struct in_addr sin_addr;
                     char  sin_zero[8];//不用,用0填充
                    }


============= Function===============================
int listen（
   SOCKET s，
   int backlog，
 ）；
s：套接口的句柄 (之前已经创建)
Backlog ：等待连接的最大队列长度
（当写为SOMAXCONN下层服务提供者将该套接字设置为最大合理值）
 eg： listen(s, 2）
如果服务器端连接数限制在2，
当有3台客户机同时发出连接请求，
第三个请求的客户端将收到“连接试图被拒绝”的错误代码 10061

===============Accpet Function=========================
=======================================================
SOCKET accept（
   SOCKET s，
   struct sockaddr* addr,
   int*addrlen
 ）；
s：套接字句柄    s
addr：指向一个缓冲区的指针（指向sockaddr_in结构的指针），
获取对方的地址信息（接收某客户机的连接请求时保存该客户端的IP地址、端口信息）
addrlen ：指向地址长度的指针
    指定addr所指空间大小，
也用于返回地址实际长度（如果addr或addrlen为NULL，则没有远程地址信息返回

======================Send Function=====================
int send （
   SOCKET s，
   const char  FAR* buf，
   int len,
   int flags
 ）；
s：已连接套接口 句柄   cli (发送对象！！！！！！）
buf：指向一个缓冲区（用来保存要收/发的数据) Sbuf
len：缓冲区长度   sizeof ( Sbuf )
flags：指定调用方式，通常设置为0
无错:返回发送/接收的字节数 isend       有错:返回SOCKET_ERROR

=====================Recv Function=====================
int recv(
 SOCKET s，
   const char  FAR* buf，
   int len,
   int flags
 );
s：已连接套接口 句柄  cli
buf：指向一个缓冲区（用来保存要收/发的数据）Rbuf
len：缓冲区长度 sizeof ( Rbuf )
flags：指定调用方式，通常设置为0



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
         //By Exp: 阻塞式！！！！！！！

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

             if (nRecv==0) //客户端已经关闭连接
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
