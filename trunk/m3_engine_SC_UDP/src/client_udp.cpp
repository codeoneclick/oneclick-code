#include "client_udp.h"

DWORD __stdcall ClientThreadSender(LPVOID value)
{
	((m3_UDPClient*)value)->SenderUpdate();
	return 0;
}

DWORD __stdcall ClientThreadListener(LPVOID value)
{
	((m3_UDPClient*)value)->ListenerUpdate();
	return 0;
}

m3_UDPClient::m3_UDPClient()
{
	_threadSenderHandle = CreateThread(NULL,NULL,ClientThreadSender,this,CREATE_SUSPENDED,NULL);
	SetThreadPriority(_threadSenderHandle,THREAD_PRIORITY_HIGHEST);
	_isAtWork = false;
}

void m3_UDPClient::Enable()
{
	 WSADATA wsaData;
	 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
     if (iResult != NO_ERROR)
	 {
         printf("Error at WSAStartup()\n");
		 return;
	 }
	 _host = gethostbyname("localhost"); 

	 if(_host == NULL) 
	 {
		 printf("No host. Error %i \n",  WSAGetLastError());
		 WSACleanup();
		 return;
	 }

	 _socketServerAddres.sin_family = _host->h_addrtype;
     memcpy((char *) &_socketServerAddres.sin_addr.s_addr, _host->h_addr_list[0], _host->h_length);
     _socketServerAddres.sin_port = htons(SERVER_PORT);

	 _socketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	 if(_socketId == INVALID_SOCKET)    
	 {
	    printf("Cannot open socket. Error %i \n",WSAGetLastError());
		WSACleanup();
		return;
	 }
	 else
		printf("Socket open \n");

	 _socketClientAddres.sin_family = AF_INET;
	 _socketClientAddres.sin_addr.s_addr = htonl(INADDR_ANY);
	 _socketClientAddres.sin_port = htons(0);

	
	 if( bind(_socketId, (struct sockaddr *) &_socketClientAddres,sizeof(_socketClientAddres)) == SOCKET_ERROR)
	 {
	    printf("Cannot bind port. Error %i \n", WSAGetLastError());
		WSACleanup();
		closesocket(_socketId);
		return;
	 }
	 else
		printf("Bind port \n");

	 _isAtWork = true;
	 ResumeThread(_threadSenderHandle);
}

void m3_UDPClient::SendMessage(m3_CS_Message _message)
{
	_message._messageHeader._messageId = _messagePool.size();
	_messagePool.push_back( _message);
}

#define MESSAGES_COUNT_PER_TICK 8

void m3_UDPClient::SenderUpdate()
{
	while(true)
	{
		unsigned int messageIndex = 0;
		std::vector<m3_CS_Message>::iterator _messageIterator = _messagePool.begin();
		while(_messageIterator != _messagePool.end())
		{
			int socketResult = sendto(_socketId, (char*)&(*_messageIterator), (*_messageIterator)._messageHeader._messageSize, 0, (struct sockaddr *) &_socketServerAddres, sizeof(_socketServerAddres));
			++messageIndex;
			if(messageIndex > MESSAGES_COUNT_PER_TICK)
				break;
			if(socketResult < 0)
			{	
				printf("Error %i \n", WSAGetLastError());
			 continue;
			}
			_messagePool.erase(_messageIterator);
			_messageIterator = _messagePool.begin();
		}
		Sleep(33);
	}
}

void m3_UDPClient::ListenerUpdate()
{

}