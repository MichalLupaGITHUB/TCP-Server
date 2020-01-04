#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class TCPClient
{

private:

public:
	TCPClient();

protected:
	sockaddr_in client; 
	int clientSize;
	SOCKET clientSocket;
	char host[NI_MAXHOST]; 
	char service[NI_MAXSERV];
};
