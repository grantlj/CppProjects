/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-18-16.59
 =============================================================*/
 #include <windows.h>
#include <IPHlpApi.h>
#include <stdio.h>
#include <time.h>
#include<Ipexport.h>
#include<Windns.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"Dnsapi")
#define Max 10 ;
//#include <winsock2.h>
#pragma comment(lib,"IPHlpApi")
void DoUsage(bool);
void DoRelease(bool);// realized
void DoRenew(bool);//realized
void DoDisplayDns(bool);
void DoFlushDns(bool);
void DoAll(void);
void GetInterfaceInfo(void);
//LPCTSTR GetNodeTypeName(UINT nodeType);
//LPCTSTR GetInterfaceTypeName(UINT InterfaceType);
 IP_ADAPTER_INDEX_MAP adapterInfo;
 PIP_INTERFACE_INFO pInfo;
DWORD checkReturn;
int main(int argc,char **argv)
{
bool doUsage=false;
bool doAll=false;
bool doRelease=false;
bool doRenew=false;
bool doDisplayDns=false;
bool doFlushDns=false;
char *argument;  //store the command line code
argument=&argv[1][1];

if((argc>1)&&(argv[1][0]=='/'))
{
  if(!strcmp(argument,"?"))
  {
    doUsage=true;
    DoUsage(doUsage);
  }
  if(!strcmp(argument,"all"))
  {
    doUsage=true;
    DoAll();


  }

  if(!strcmp(argument,"release"))
  {
    doRelease=true;
 DoRelease(doRelease);
  }

  if(!strcmp(argument,"renew"))
  {
    doRenew=true;
    DoRenew(doRenew);

  }

  if(!strcmp(argument,"displaydns"))
  {
    doDisplayDns=true;
    DoDisplayDns(doDisplayDns);

  }

  if(!strcmp(argument,"flushdns"))
  {
    doFlushDns=true;
    DoFlushDns(doFlushDns);

  }

}
else
printf("error command code!");
printf("......................................");

}


/* get the using adapter information*/

void  GetInterfaceInfo()
{

    ULONG outBufferLen=0;
    pInfo=(IP_INTERFACE_INFO *)malloc(sizeof(IP_INTERFACE_INFO));
/* Make the first call to buffer information*/
  if((checkReturn=GetInterfaceInfo(pInfo,&outBufferLen))==ERROR_INSUFFICIENT_BUFFER)
  {
    free(pInfo);
    pInfo=(IP_INTERFACE_INFO *)malloc(outBufferLen);

  }

/* Make the second call of GetInterfaceInfo() to get the actual data */

  if((checkReturn=GetInterfaceInfo(pInfo,&outBufferLen))==NO_ERROR)
  {
    adapterInfo=pInfo->Adapter[0];//关键此处返回IP_ADAPTER_INDEX_MAP 用于IP更新
    printf("the dapter name is: %d ",pInfo->Adapter[0].Name);


  }
    else
  {

        printf("Get the interface information occer error!");


  }


}



/* release IP address */

void DoRelease(bool doRelease)
{
  if(doRelease)
  {

  GetInterfaceInfo();
/**the specific action to config/release*/
    if((checkReturn=IpReleaseAddress(&adapterInfo))==NO_ERROR)
 {
     printf("the action of release IP work!");
 }
    else
      printf("An error occured while releasing interface of %s",pInfo->Adapter[0].Name);

}
  else
  {
  printf("illegal action");

  }

}

/** Do renew IPAddree */

void DoRenew(bool doRenew)
{

 if(doRenew)
 {
 GetInterfaceInfo();

 if((checkReturn=IpRenewAddress(&adapterInfo))==NO_ERROR)
 {
     printf("the action of release IP work!");
 }
    else
      printf("An error occured while releasing interface of %s",pInfo->Adapter[0].Name);

 }

 else
  {
  printf("illegal action");

  }
}

/* display all information  ipconfig/all */


void DoAll(void)

{

    DWORD  returnCheckError;
    PFIXED_INFO pFixedInfo;
    DWORD FixedInfoSize = 0;

    PIP_ADDR_STRING pAddrStr;
 PIP_ADAPTER_INFO pAdapt,pAdapterInfo;

    if ((returnCheckError = GetNetworkParams(NULL, &FixedInfoSize)) != 0)
    {
        if (returnCheckError != ERROR_BUFFER_OVERFLOW)
        {
            printf("GetNetworkParams sizing failed with error %d\n", returnCheckError);
            return;
        }
    }

    // Allocate memory from sizing information
    if ((pFixedInfo = (PFIXED_INFO) malloc( FixedInfoSize)) == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    if ((returnCheckError = GetNetworkParams(pFixedInfo, &FixedInfoSize)) == 0)
    {
        printf("\tHost Name . . . . . . . . . : %s\n", pFixedInfo->HostName);
        printf("\tDNS Servers . . . . . . . . : %s\n", pFixedInfo->DnsServerList.IpAddress.String);
        pAddrStr = pFixedInfo->DnsServerList.Next;
        while(pAddrStr)
        {
            printf("%52s\n", pAddrStr->IpAddress.String);
            pAddrStr = pAddrStr->Next;
        }

        printf("\tNode Type . . . . . . . . . : ");
        switch (pFixedInfo->NodeType)
        {
            case 1:
                printf("%s\n", "Broadcast");
                break;
            case 2:
                printf("%s\n", "Peer to peer");
                break;
            case 4:
                printf("%s\n", "Mixed");
                break;
            case 8:
                printf("%s\n", "Hybrid");
                break;
            default:
                printf("\n");
        }

        printf("\tNetBIOS Scope ID. . . . . . : %s\n", pFixedInfo->ScopeId);
        printf("\tIP Routing Enabled. . . . . : %s\n", (pFixedInfo->EnableRouting ? "yes" : "no"));
        printf("\tWINS Proxy Enabled. . . . . : %s\n", (pFixedInfo->EnableProxy ? "yes" : "no"));
        printf("\tNetBIOS Resolution Uses DNS : %s\n", (pFixedInfo->EnableDns ? "yes" : "no"));
    } else
    {
        printf("GetNetworkParams failed with error %d\n", returnCheckError);
        return;
    }



 //
    // Enumerate all of the adapter specific information using the IP_ADAPTER_INFO structure.
    // Note:  IP_ADAPTER_INFO contains a linked list of adapter entries.

    ULONG AdapterInfoSize = 0;
    if ((returnCheckError = GetAdaptersInfo(NULL, &AdapterInfoSize)) != 0)
    {
        if (returnCheckError != ERROR_BUFFER_OVERFLOW)
        {
            printf("GetAdaptersInfo sizing failed with error %d\n", returnCheckError);
            return;
        }
    }

    // Allocate memory from sizing information
    if ((pAdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc(GPTR, AdapterInfoSize)) == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    // Get actual adapter information
    if ((returnCheckError = GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize)) != 0)
    {
        printf("GetAdaptersInfo failed with error %d\n", returnCheckError);
        return;
    }

    pAdapt = pAdapterInfo;

    while (pAdapt)
    {
        switch (pAdapt->Type)
        {
            case MIB_IF_TYPE_ETHERNET:
                printf("\nEthernet adapter ");
                break;
            case MIB_IF_TYPE_TOKENRING:
                printf("\nToken Ring adapter ");
                break;
            case MIB_IF_TYPE_FDDI:
                printf("\nFDDI adapter ");
                break;
            case MIB_IF_TYPE_PPP:
                printf("\nPPP adapter ");
                break;
            case MIB_IF_TYPE_LOOPBACK:
                printf("\nLoopback adapter ");
                break;
            case MIB_IF_TYPE_SLIP:
                printf("\nSlip adapter ");
                break;
            case MIB_IF_TYPE_OTHER:
            default:
                printf("\nOther adapter ");
        }
        printf("%s:\n\n", pAdapt->AdapterName);

        printf("\tDescription . . . . . . . . : %s\n", pAdapt->Description);

        printf("\tPhysical Address. . . . . . : ");
        for (UINT i=0; i<pAdapt->AddressLength; i++)
        {
            if (i == (pAdapt->AddressLength - 1))
                printf("%.2X\n",(int)pAdapt->Address[i]);
            else
                printf("%.2X-",(int)pAdapt->Address[i]);
        }

        printf("\tDHCP Enabled. . . . . . . . : %s\n", (pAdapt->DhcpEnabled ? "yes" : "no"));

        pAddrStr = &(pAdapt->IpAddressList);
        while(pAddrStr)
        {
            printf("\tIP Address. . . . . . . . . : %s\n", pAddrStr->IpAddress.String);
            printf("\tSubnet Mask . . . . . . . . : %s\n", pAddrStr->IpMask.String);
            pAddrStr = pAddrStr->Next;
        }

        printf("\tDefault Gateway . . . . . . : %s\n", pAdapt->GatewayList.IpAddress.String);
        pAddrStr = pAdapt->GatewayList.Next;
        while(pAddrStr)
        {
            printf("%52s\n", pAddrStr->IpAddress.String);
            pAddrStr = pAddrStr->Next;
        }

        printf("\tDHCP Server . . . . . . . . : %s\n", pAdapt->DhcpServer.IpAddress.String);
        printf("\tPrimary WINS Server . . . . : %s\n", pAdapt->PrimaryWinsServer.IpAddress.String);
        printf("\tSecondary WINS Server . . . : %s\n", pAdapt->SecondaryWinsServer.IpAddress.String);

        struct tm *newtime;

        // Display coordinated universal time - GMT
        newtime = gmtime(&pAdapt->LeaseObtained);
        printf( "\tLease Obtained. . . . . . . : %s", asctime( newtime ) );

        newtime = gmtime(&pAdapt->LeaseExpires);
        printf( "\tLease Expires . . . . . . . : %s", asctime( newtime ) );

        pAdapt = pAdapt->Next;
    }
}

void DoUsage(bool doUsage)
{

 if(doUsage)
 {
 printf("\nUSAGE:\n"
    "    ipconfig [/? | /all | /renew [adapter] | /release [adapter] |\n"
    "              /flushdns | /displaydns | /registerdns |\n"
    "              /showclassid adapter |\n"
    "              /setclassid adapter [classid] ]\n"
    "\n"
    "where\n"
    "    adapter        Connection name\n"
    "                  (wildcard characters * and ? allowed, see examples)\n"
    "\n"
    "    Options:\n"
    "      /?          Display this help message\n"
    "      /all        Display full configuration information.\n"
    "      /release    Release the IP address for the specified adapter.\n"
    "      /renew      Renew the IP address for the specified adapter.\n"
    "      /flushdns    Purges the DNS Resolver cache.\n"
    "      /registerdns Refreshes all DHCP leases and re-registers DNS names.\n"
    "      /displaydns  Display the contents of the DNS Resolver Cache.\n"
    "      /showclassid Displays all the dhcp class IDs allowed for adapter.\n"
    "      /setclassid  Modifies the dhcp class id.\n"
    "\n"
    "The default is to display only the IP address, subnet mask and\n"
    "default gateway for each adapter bound to TCP/IP.\n"
    "\n"
    "For Release and Renew, if no adapter name is specified, then the IP address\n"
    "leases for all adapters bound to TCP/IP will be released or renewed.\n"
    "\n"
    "For Setclassid, if no ClassId is specified, then the ClassId is removed.\n"
    "\n"
    "Examples:\n"
    "    > ipconfig                  ... Show information.\n"
    "    > ipconfig /all              ... Show detailed information\n"
    "    > ipconfig /renew            ... renew all adapters\n"
    "    > ipconfig /renew EL*        ... renew any connection that has its\n"
    "                                    name starting with EL\n"
    "    > ipconfig /release *Con*    ... release all matching connections,\n"
    "                                    eg. \"Local Area Connection 1\" or\n"
    "                                        \"Local Area Connection 2\"\n");




 }

 else
 {
 printf("ilegal code!");

 }



}
void DoDisplayDns(bool doDisplayDns)

{
if(doDisplayDns)
{
    char hostname[256];
 int iRet = 0;
 WSADATA wsaData;

    DNS_STATUS status;              //Return value of  DnsQuery_A() function.
    PDNS_RECORD pDnsRecord;
 int assignBuffLenght;
 assignBuffLenght=(sizeof(DNS_RECORD))*Max;
 pDnsRecord=(DNS_RECORD*)malloc(assignBuffLenght);
 memset(pDnsRecord,0,assignBuffLenght);


 if (WSAStartup(MAKEWORD(2,1),&wsaData)) //调用Windows Sockets DLL
 {
  printf("Winsock无法初始化!\n");
  WSACleanup();

 }

 memset(hostname, 0, 256);
 iRet = gethostname(hostname, sizeof(hostname));
 if(iRet != 0 )
 {
  printf( "get hostname error:%d\n", iRet);
 }
 printf("%s\n", hostname);




 LPSTR pOwnerName=hostname;

      // Calling function DnsQuery to query Host or PTR records
    status = DnsQuery(pOwnerName,                //Pointer to OwnerName.
                        DNS_TYPE_A,                      //Type of the record to be queried.
                        DNS_QUERY_STANDARD,    // Bypasses the resolver cache on the lookup.
                        NULL,                  //Contains DNS server IP address.
                        &pDnsRecord,                //Resource record that contains the response.
                        NULL);                    //Reserved for future use.

    //  printf("The host name is %s  \n",(pDnsRecord->Data.PTR.pNameHost));
 while(pDnsRecord){
   printf("The host name is  %s \n",pDnsRecord->pName);
   printf("the type is %d \n",pDnsRecord->wType);
   printf("the lenght of data is %d \n", pDnsRecord->wDataLength);
   printf(" the time to live is  %d \n", pDnsRecord-> dwTtl);
   printf("the lenght of data id %d \n", pDnsRecord-> dwReserved);

        pDnsRecord=pDnsRecord->pNext;
 }


printf("dnsCache print over");
}
else
{
printf("ilegal code");

}

}


void DoFlushDns(bool){


printf("relizing config/flushdns!");



}
