#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "TCPClient.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class TCPServer: public TCPClient
{

private:
	WSADATA wsData;
	WORD ver;
	int wsOk;

	SOCKET listening;

	sockaddr_in hint;

	TCPClient::client;
	TCPClient::clientSize;
	TCPClient::clientSocket;
	TCPClient::host;
	TCPClient::service;

	char buf[4096];
	int bytesReceived;

	void TCPServer_Init();
	void TCPServer_Bind_IP_Port();
	void TCPServer_StartListening();
	void TCPServer_AcceptClient();
	void TCPServer_StopListening();
	void TCPServer_DataExchange();
	void TCPServer_CloseSocket();

public:
	TCPServer();
	void ServerRun();

protected:
		//
};
