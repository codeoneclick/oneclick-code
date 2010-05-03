#pragma once
#ifndef _M3_UDPSERVER_H_
#define _M3_UDPSERVER_H_

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")

#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "m3_UDPClient.h"

#define SERVER_PORT 6633

#define MESSAGE_BUFFER_MAX_SIZE 1024

DWORD __stdcall ServerThread(LPVOID value);

class m3_UDPServer
{
private :
	SOCKET _socketId;
	struct sockaddr_in _socketClientAddres;
	struct sockaddr_in _socketServerAddres;
	char *_messageBuffer;
	m3_MessageHeader *_messagePtr;
	bool _isAtWork;
	HANDLE _thread;
public :
	m3_UDPServer();
	void Enable();
	void Disable();
	void Update();
	__forceinline bool IsAtWork() { return _isAtWork; }
};

#endif