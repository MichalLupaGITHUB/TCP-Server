#include "TCPServer.h"

// Constructor
TCPServer::TCPServer()
{

}

// Initialization
void TCPServer::TCPServer_Init()
{
	ver = MAKEWORD(2, 2);

	wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Cannot create connection" << endl;
		return;
	}
}

// Binding IP with Port
void TCPServer::TCPServer_Bind_IP_Port()
{
	listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET)
	{
		cerr << "Cannot create connection" << endl;
		return;
	}

	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listening, (sockaddr*)&hint, sizeof(hint));
}

// Start listening
void TCPServer::TCPServer_StartListening()
{
	listen(listening, SOMAXCONN);
}

// Accepting Clinet connection
void TCPServer::TCPServer_AcceptClient()
{
	clientSize = sizeof(client);
	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Cannot create socket" << endl;
		return;
	}

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << "Connected on PORT: " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "Connected on PORT: " << ntohs(client.sin_port) << endl;
	}
}

// Stop listening
void TCPServer::TCPServer_StopListening()
{
	closesocket(listening);
}

// Data exchanging
void TCPServer::TCPServer_DataExchange()
{
	while (true)
	{
		ZeroMemory(buf, 4096);

		bytesReceived = recv(clientSocket, buf, 4096, 0);

		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Data received FAULT" << endl;
			break;
		}
		if (bytesReceived == 0)
		{
			cout << "Client disconnected" << endl;
			break;
		}

		if (bytesReceived > 0)
		{
			cout << buf << endl;
		}

		send(clientSocket, buf, bytesReceived + 1, 0);
	}

	closesocket(clientSocket);
}

// Closing socket
void TCPServer::TCPServer_CloseSocket()
{
	WSACleanup();
}

// Server Run
void TCPServer::ServerRun()
{
	TCPServer_Init();
	TCPServer_Bind_IP_Port();
	TCPServer_StartListening();
	TCPServer_AcceptClient();
	TCPServer_StopListening();
	TCPServer_DataExchange();
	TCPServer_CloseSocket();
}