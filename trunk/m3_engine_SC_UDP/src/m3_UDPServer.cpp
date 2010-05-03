#include "m3_UDPServer.h"

DWORD __stdcall ServerThread(LPVOID value)
{
	((m3_UDPServer*)value)->Update();
	return 0;
}

m3_UDPServer::m3_UDPServer()
{
	_thread = CreateThread(NULL,NULL,ServerThread,this,CREATE_SUSPENDED,NULL);
	SetThreadPriority(_thread,THREAD_PRIORITY_HIGHEST);
	_isAtWork = false;
	_messageBuffer = new char[MESSAGE_BUFFER_MAX_SIZE];
}

void m3_UDPServer::Update()
{
	while(true)
	{
		 int structSize = sizeof(_socketClientAddres);
		 if(recvfrom(_socketId, _messageBuffer, MESSAGE_BUFFER_MAX_SIZE, 0,(struct sockaddr *) &_socketClientAddres, &structSize) > 0)
		 {	
			 _messagePtr = (m3_MessageHeader*)_messageBuffer;
			 Vector3d *vPosition = (Vector3d*)( _messageBuffer + sizeof(m3_MessageHeader));
			 printf("from %s:UDP%u : %f, %f, %f . \n",inet_ntoa(_socketClientAddres.sin_addr),ntohs(_socketClientAddres.sin_port),vPosition->x,vPosition->y,vPosition->z);
		 }
		 else
			 printf("Error %i \n", WSAGetLastError());
	}
}

void m3_UDPServer::Enable()
{
	 WSADATA wsaData;
	 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
     if (iResult != NO_ERROR)
	 {
         printf("Error at WSAStartup()\n");
		 return;
	 }

	 _socketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	 if(_socketId == INVALID_SOCKET)    
	 {
	    printf("Cannot open socket. Error %i \n",WSAGetLastError());
		WSACleanup();
		return;
	 }
	 else
		printf("Socket open \n");

	  _socketServerAddres.sin_family = AF_INET;
	  _socketServerAddres.sin_addr.s_addr = inet_addr("127.0.0.1");
	  _socketServerAddres.sin_port = htons(SERVER_PORT);

	
	  if( bind(_socketId, (struct sockaddr *) &_socketServerAddres,sizeof(_socketServerAddres)) == SOCKET_ERROR)
	  {
	    printf("Cannot bind port. Error %i \n", WSAGetLastError());
		WSACleanup();
		closesocket(_socketId);
		return;
	  }
	  else
		printf("Bind port \n");

    printf("Ready  to listen...");
	_isAtWork = true;
	ResumeThread(_thread);

}


void m3_UDPServer::Disable()
{
	SuspendThread(_thread);
}