#include <iostream>
#include <string>
#include <time.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define PORT_1 (2000)
#define LOG_BACK (10)
#define MAX_ATTEMP_TIMES (10)

void cleanSocket(SOCKET s)
{
	closesocket(s);
	WSACleanup();
}

int main(int argc, char* argv[])
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (INVALID_SOCKET == clientSocket)
	{
		cout << "Socket initialization failed£¡" << endl;
		system("pause");
		cleanSocket(clientSocket);
		return 0;
	}

	SOCKADDR_IN serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT_1);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.7");

	int curAttempTimes = 0;
	int returnCode = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	while (0 != returnCode && curAttempTimes<MAX_ATTEMP_TIMES)
	{
		cout << "Cannot connect to the Server at the moment! " 
			 << "(Current Attempt times: "<<curAttempTimes+1 <<")" <<endl;
		Sleep(2000);
		curAttempTimes++;
		returnCode = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	}
	if (curAttempTimes == MAX_ATTEMP_TIMES)
	{
		cout << endl;
		cout << "Connection Faied!" << endl;
		system("pause");
		cleanSocket(clientSocket);
		return 0;
	}
	//system("cls");
	cout << "Successfully Connect to the Server!" << endl;

	string sendMsg="";
	while (true)
	{
		cout << "to Server:" << endl;
		cin >> sendMsg;
		send(clientSocket, (char*)(sendMsg.data()), sizeof(sendMsg), 0);
		if (sendMsg=="quit")
		{
			cout << "Quit connection!" << endl;
			system("pause");
			break;
		}
	}
	
	cleanSocket(clientSocket);
	return 0;
}