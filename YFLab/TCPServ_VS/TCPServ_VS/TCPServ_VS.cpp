

#include "stdafx.h"

#include <stdio.h>
#include <afxinet.h>

#include <afx.h>

#include <atlstr.h>
#include <fstream>

#include <afxwin.h>
#include <UrlMon.h>
#pragma comment(lib, "urlmon.lib")

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
using namespace std;
#include <shellapi.h>
#pragma comment(lib,"shell32.lib")


unsigned char cmdtoSend[3];

void sendLightAndRemoteState()
{
	char* destUrl = new char[255];
	sprintf(destUrl, "http://grantlj.gicp.net:8080/YFLab/GetData?reqType=lightState&rnd=%d",
		rand() * 80000);

	TCHAR tdestUrl[255];
	MultiByteToWideChar(CP_ACP, 0, destUrl, -1, tdestUrl, 255);

	CString strHtml = "";   //存放网页数据

	HRESULT hr = URLDownloadToFile(0, tdestUrl,
		_T("D:\\light.dat"), 0, NULL);

	DeleteUrlCacheEntry(tdestUrl);

	int t = -1;
	if (hr == S_OK)
	{
		FILE* f=fopen("D:\\light.dat", "r");
		char str[255];
		fgets(str, sizeof(str), f);
		fclose(f);
        
		
		t = (str[29] - '0') * 10;

		if (str[30] >= '0' && str[30] <= '9')
			t = t + (str[30] - '0');
	}

	int dig[10];
	int count = 0;
	while (t > 0)
	{
		dig[count] = t % 2;
		t /= 2;
		count++;
	}



	int lightState1 = dig[0];
	int lightState2 = dig[1];

	
	
	cmdtoSend[0] = 2;
	cmdtoSend[1] = lightState1;

	cout << lightState1 << "light" << endl;
	
    
	//Get remote state.
//	char* destUrl = new char[255];
	sprintf(destUrl, "http://grantlj.gicp.net:8080/YFLab/GetData?reqType=remoteState&rnd=%d",
		rand() * 80000);

//	TCHAR tdestUrl[255];
	MultiByteToWideChar(CP_ACP, 0, destUrl, -1, tdestUrl, 255);

	//CString strHtml = "";   //存放网页数据

	 hr = URLDownloadToFile(0, tdestUrl,
		_T("D:\\remote.dat"), 0, NULL);
	 DeleteUrlCacheEntry(tdestUrl);
	t = -1;
	if (hr == S_OK)
	{
		FILE* f = fopen("D:\\remote.dat", "r");
		char str[255];
		fgets(str, sizeof(str), f);
		fclose(f);
		if (str[20] == '}')
			t = str[19] - '0';
		else
			t = (str[19] - '0') * 10 + (str[20] - '0');
		cmdtoSend[2] = t;
		cout << t << "hi" << endl;
	}

	//cmdtoSend[2]=1;
	//cout << cmdtoSend [0]<<" "<<cmdtoSend[1]<<" "<<cmdtoSend[2]<<endl;

}


void sendData(int junction, 
	          int lightState_1, int lightState_2, 
			  int temperature, int humidity,
			  int smog,int infrared,
			  int power_h,int power_l,
			  int total)
{
	
	//cout << "in" << endl;
	//CString destUrl;
	//destUrl.Format((wchar_t)("grantlj.gicp.net:8080/YFLab/SetData?reqType=sensorData&junction=%d&light1=%d&light2=%d&temperature=%d&humidity=%d"), junction, lightState_1, lightState_2, temperature, humidity);

	cout << junction <<" "<< lightState_1<<" "<< lightState_2<<" " << temperature<<" " << humidity <<" "<<smog<<" "<<infrared<<" "<<power_h<<" "<<power_l<<" "<<total<<"   !!!" << endl;
	

		char* destUrl = new char[255];

		srand(time(NULL));

		sprintf(destUrl, "http://grantlj.gicp.net:8080/YFLab/SetData?reqType=sensorData&junction=%d&light1=%d&light2=%d&temperature=%d&humidity=%d&infrared=%d&smog=%d&power_hi=%d&power_lo=%d&total=%d&rnd=%d&remote=0",
			junction,
			lightState_1,
			lightState_2,
			temperature,
			humidity,
			smog,
			infrared,
			power_h,
			power_l,
			total,
			rand() * 35000);

		TCHAR tdestUrl[255];
		MultiByteToWideChar(CP_ACP, 0, destUrl, -1, tdestUrl, 255);
		DeleteUrlCacheEntry(tdestUrl);
		CInternetSession session;
		CHttpFile *file = NULL;

		CString strHtml = "";   //存放网页数据

		try{
			file = (CHttpFile*)session.OpenURL(tdestUrl);

			//cout << "ok" << endl;
		}
		catch (CInternetException * m_pException){
			//cout << "fail!" << endl;
			cout << "uploading data to server failed." << endl;
			file = NULL;
			m_pException->m_dwError;
			m_pException->Delete();
			//	session.Close();
			//MessageBox("CInternetException");
		}

		

		CString strLine;
		if (file != NULL){
		while (file->ReadString(strLine) != NULL){
		strHtml += strLine;
		}
		//cout << "not null" << endl;

		}

		
		session.Close();
		if (file != NULL)
		{
			file->Close();
			delete file;
			file = NULL;
		}

		sendLightAndRemoteState();
	




	//ShellExecute(NULL, L"open", L"iexplore.exe", tdestUrl, NULL, SW_SHOW);

}

int main(int argc, char **argv)
{   

	CWinApp app((LPCTSTR)argv[0]);
	app.InitApplication();
	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
	
	/*
	int i = 0;
	do
	{
		i++;
		//sendData(junction, !lightState_1,!lightState_2, temperature, humidity,smog,infrared,power_h,power_l,total);
		sendData(1, 1, 1, 25-i,34+i , 0, 1, 1, 10, 35);
		Sleep(1000);
	} while (true);
	*/
	//===========================================================
	//===========================================================
	//Load Necessary Library;
	printf("Loading Necessary Library...\n");
	//Generate WinSock Version.
	//HI: Vice Version Info.
	//LO: Main Version Info.
	WORD wVersionRequested = MAKEWORD(2, 2);
	//WSADATA is a structure to SAVE INITIAL INFORMATION!!!!
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
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

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//AF_INET: Internet Standard;
	//SOCKET_STREAM: TCP;
	//IPPROTO_TCP: TCP standard PROTOL!

	if (s == INVALID_SOCKET)
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

	Sadd.sin_family = AF_INET;
	Sadd.sin_port = htons(1400); //if it is 0 then random by system!!!

	//INADDR_ANY: means IGNORE PC'S REAL IP!!!!!ANY IS OK!!!!!
	//Bind IP INFO(Sadd) to Socket(s)!!!!!!!!!!!!!!!!!!!!!!!!!!

	Sadd.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// Sadd.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	if (bind(s, (sockaddr*)&Sadd, sizeof(Sadd)) == SOCKET_ERROR)
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
	if (listen(s, 100) == SOCKET_ERROR)
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
	int addLen = sizeof(clientadd);

	SOCKET cli;
	char Rbuf[10];
	
	memset(Rbuf, 0, sizeof(Rbuf));
	int nRecv;
	cli = accept(s, (sockaddr*)&clientadd, &addLen);
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

		cout << "Receive a new message from IP:" << inet_ntoa(clientadd.sin_addr) << " & Port is:" <<
			ntohs(clientadd.sin_port) << endl;

		nRecv = recv(cli, Rbuf, sizeof(Rbuf), 0);
		

		//cout << Rbuf << "!!!" << endl;

		if (nRecv == 0) //客户端已经关闭连接
			printf("Client has closed the connection\n");

		if (nRecv == SOCKET_ERROR)
		{
			//printf("recv failed.\n");
			//  printf("Get message from client::::%s",Rbuf);
			//continue;
		}
		else
		{
			int junction = Rbuf[0];
			int lightState_1 = Rbuf[1];
			int lightState_2 = Rbuf[2];
			int temperature = Rbuf[3];
			int humidity = Rbuf[4];
			int smog = Rbuf[5];
			int infrared = Rbuf[6];
			int power_h = Rbuf[7];
			int power_l = Rbuf[8];
			int total = Rbuf[9];


			//cout << junction << "," << lightState_1 << "," << temperature << "," << humidity << endl;
			if (junction == 1)
				sendData(junction, lightState_1, lightState_2, temperature, humidity, smog, infrared, power_h, power_l, total);
			else
				cout << "junction:"<<junction << endl;
		}

		
     	send(cli,(char*) cmdtoSend,sizeof(cmdtoSend),0);

		/*
		if (isend==SOCKET_ERROR)
		{
		printf("Send Message to Client failed...\n 
		printf("Error Code:%d\n",WSAGetLastError());
		continue;
		}
		else
		printf("Message [%s] sended successfully.\n",Sbuf);

		SleepEx(1000,true);
		*/

		SleepEx(2000, true);

	}
	closesocket(s);
	WSACleanup();
	return 0;

}
