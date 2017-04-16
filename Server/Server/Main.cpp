#include <iostream>
#include <string>
#include <time.h>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

#define PORT_1 (2000)
#define BACK_LOG (10)

int main(int argc, char* argv[])
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (INVALID_SOCKET == serverSocket)
	{
		cout << "Socket initialization failed!" << endl;
		system("pause");
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	SOCKADDR_IN serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT_1);
	serverAddr.sin_addr.S_un.S_addr = (INADDR_ANY);

	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, BACK_LOG);
	
	SOCKET clientSocket;
	SOCKADDR_IN clientAddr;
	int len = sizeof(SOCKADDR_IN);
	cout << "Status: Wating for client connetion!" << endl<<endl;
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &len);
	char *clientIP = inet_ntoa(clientAddr.sin_addr);
	u_short clientPortNum =ntohs(clientAddr.sin_port);
	
	cout << "Client connected!\t"<< endl;
	cout << "Client IP: " << clientIP << endl;
	cout << "Port Number: " << clientPortNum << endl<<endl;

	string recvMsg;
	while (true)
	{
		recvMsg = "";
		recv(clientSocket, (char*)(recvMsg.data()), sizeof(recvMsg), 0);
		if (recvMsg=="quit")
		{
		cout << endl;
		cout << "From Client:" << endl;
		cout << "Client quit connection!" <<endl;
		system("pause");
		}
		cout << "From Client:" << endl;
		cout << recvMsg << endl;
	}

	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}