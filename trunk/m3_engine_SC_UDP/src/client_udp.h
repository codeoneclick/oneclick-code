#pragma once
#ifndef _M3_UDPCLIENT_H_
#define _M3_UDPCLIENT_H_

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")

#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "Vector3d.h"

DWORD __stdcall ClientThreadSender(LPVOID value);
DWORD __stdcall ClientThreadListener(LPVOID value);

#define SERVER_PORT 6633

struct m3_MessageHeader
{
	unsigned int _messageId;
	unsigned int _messageType;
	unsigned int _messageSize;
};


struct m3_CS_Message
{
	m3_MessageHeader _messageHeader;
	Vector3d vPosition;
	Vector3d vRotation;
};

class m3_UDPClient
{
private :
	SOCKET _socketId;
	struct sockaddr_in _socketClientAddres;
	struct sockaddr_in _socketServerAddres;
	struct hostent *_host;
	std::vector<m3_CS_Message> _messagePool;
	bool _isAtWork;
	HANDLE _threadSenderHandle;
	HANDLE _threadListenerHandle;
	void _Ping();
public :
	m3_UDPClient();
	void Enable();
	void Disable();
	void ListenerUpdate();
	void SenderUpdate();
	void SendMessage(m3_CS_Message _message);
	__forceinline bool IsAtWork() { return _isAtWork; }
};

#endif
