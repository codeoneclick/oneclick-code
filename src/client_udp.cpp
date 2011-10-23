#include "client_udp.h"

DWORD __stdcall client_listener_thread(void* in_value)
{
	((client_udp*)in_value)->_update_sender();
	return 0;
}

DWORD __stdcall client_sender_thread(void* in_value)
{
	((client_udp*)in_value)->_update_listener();
	return 0;
}

client_udp::client_udp()
{
	InitializeCriticalSection(&_client_critical_section);

	_thread_sender_handle = CreateThread(NULL,NULL,client_sender_thread,this,CREATE_SUSPENDED,NULL);
	SetThreadPriority(_thread_sender_handle,THREAD_PRIORITY_HIGHEST);
	_thread_listener_handle = CreateThread(NULL,NULL,client_listener_thread,this,CREATE_SUSPENDED,NULL);
	SetThreadPriority(_thread_listener_handle,THREAD_PRIORITY_HIGHEST);

	 _message_buffer = new char[MESSAGE_BUFFER_MAX_SIZE];

	_is_working = false;
}

void client_udp::init()
{
	 WSADATA wsa_data;
     if (WSAStartup(MAKEWORD(2,2), &wsa_data) != NO_ERROR)
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

	 _server_socket_addr.sin_family = _host->h_addrtype;
     memcpy((char *) &_server_socket_addr.sin_addr.s_addr, _host->h_addr_list[0], _host->h_length);
     _server_socket_addr.sin_port = htons(SERVER_PORT);

	 _socket_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	 if(_socket_id == INVALID_SOCKET)    
	 {
	    printf("Cannot open socket. Error %i \n",WSAGetLastError());
		WSACleanup();
		return;
	 }
	 else
		printf("Socket open \n");
}

void client_udp::enable()
{
	 _is_working = true;
	 ResumeThread(_thread_sender_handle);
	 ResumeThread(_thread_listener_handle);
}

void client_udp::send_message(message_ext *message)
{
	EnterCriticalSection(&_client_critical_section);
	message->header.message_id = _message_pool.size();
	_message_pool.push_back((*message));
	LeaveCriticalSection(&_client_critical_section);
}

void client_udp::_update_sender()
{
	while(true)
	{
		unsigned int message_index = 0;
		EnterCriticalSection(&_client_critical_section);
		std::vector<message_ext>::iterator _message_iterator = _message_pool.begin();
		while(_message_iterator != _message_pool.end())
		{
			int socket_result = sendto(_socket_id, (char*)&(*_message_iterator), (*_message_iterator).header.message_size + sizeof(message_header), 0, (struct sockaddr *) &_server_socket_addr, sizeof(_server_socket_addr));
			Vector3d *temp = (Vector3d*)(*_message_iterator).data;
			++message_index;
			if(message_index > MESSAGES_COUNT_PER_TICK)
				break;
			if(socket_result < 0)
			{	
				printf("Error %i \n", WSAGetLastError());
			 continue;
			}
			_message_pool.erase(_message_iterator);
			_message_iterator = _message_pool.begin();
		}
		LeaveCriticalSection(&_client_critical_section);
		Sleep(66);
	}
}

void client_udp::_update_listener()
{
	while(true)
	{
		 int server_sett_size = sizeof(_server_socket_addr);
		 if(recvfrom(_socket_id, _message_buffer, MESSAGE_BUFFER_MAX_SIZE, 0,(struct sockaddr *) &_server_socket_addr, &server_sett_size) > 0)
		 {	
			 message_ext *message = (message_ext*)_message_buffer;
			 switch(message->header.message_type)
			 {
			     case CS_CONNECT :
						 printf("--- info --- client catch message\n");
				 break;
			 }
		 }
		 else
			 printf("Error %i \n", WSAGetLastError());
	}
}