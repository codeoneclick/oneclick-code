#ifndef CNETWORKCONTROLLER_H
#define CNETWORKCONTROLLER_H
#pragma once

#include <windows.h>

#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")

#define k_SERVER_PORT 1986
#define k_SERVER_IP "127.0.0.1"
#define k_HEADER_SIZE 8

class CNetworkController
{
private :
	static CNetworkController* m_controller;
	struct hostent *m_host;
	struct sockaddr_in m_serverSocket_addr;
	unsigned int m_socket;
public :
	CNetworkController();
	~CNetworkController();
	static CNetworkController* Instance();
	bool Connect();
	bool Send(const char* _data, unsigned int _size);
	void Disconnect();
};

#endif