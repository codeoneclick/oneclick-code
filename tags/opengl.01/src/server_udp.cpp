#include "server_udp.h"

DWORD __stdcall server_listener_thread(void *in_value)
{
	((server_udp*)in_value)->_update_listener();
	return 0;
}

DWORD __stdcall server_sender_thread(void *in_value)
{
	((server_udp*)in_value)->_update_sender();
	return 0;
}

server_udp::server_udp()
{
	InitializeCriticalSection(&_server_critical_section);

	_thread_listener_handle = CreateThread(NULL,NULL,server_listener_thread,this,CREATE_SUSPENDED,NULL);
	SetThreadPriority(_thread_listener_handle,THREAD_PRIORITY_HIGHEST);
	
	_thread_sender_handle = CreateThread(NULL,NULL,server_sender_thread,this,CREATE_SUSPENDED,NULL);
	SetThreadPriority(_thread_sender_handle,THREAD_PRIORITY_LOWEST);
	
    _message_buffer = new char[MESSAGE_BUFFER_MAX_SIZE];
	_is_working = false;
}

void server_udp::init()
{
	 WSADATA wsa_data;
     if(WSAStartup(MAKEWORD(2,2), &wsa_data) != NO_ERROR)
	 {
         printf("Error at WSAStartup()\n");
		 return;
	 }

	 if((_socket_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)    
	 {
	    printf("Cannot open socket. Error %i \n",WSAGetLastError());
		WSACleanup();
		return;
	 }
	 else
		printf("Socket open \n");

	  _server_socket_addr.sin_family = AF_INET;
	  _server_socket_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	  _server_socket_addr.sin_port = htons(SERVER_PORT);

	  if(bind(_socket_id, (struct sockaddr *) &_server_socket_addr,sizeof(_server_socket_addr)) == SOCKET_ERROR)
	  {
	    printf("Cannot bind port. Error %i \n", WSAGetLastError());
		WSACleanup();
		closesocket(_socket_id);
		return;
	  }
	  else
		printf("Bind port \n");

    printf("Ready  to listen...");
}

void server_udp::_update_listener()
{
	while(true)
	{
		 int client_sett_size = sizeof(_client_socket_addr);
		 if(recvfrom(_socket_id, _message_buffer, MESSAGE_BUFFER_MAX_SIZE, 0,(struct sockaddr *) &_client_socket_addr, &client_sett_size) > 0)
		 {	
			 message_ext *message = (message_ext*)_message_buffer;
			 std::string ip_str = inet_ntoa(_client_socket_addr.sin_addr);
			 switch(message->header.message_type)
			 {
			     case CS_CONNECT :
					
					 if(_clients_messages_pool.find(ip_str) != _clients_messages_pool.end())
					 {
						 printf("--- warning --- client %s try to register in the second time.\n",ip_str.c_str());
						 break;
					 }
					 else
					 {	
						 _clients_messages_pool[ip_str] = new client_params();
						 _clients_messages_pool[ip_str]->ip_str = ip_str;
					     _clients_messages_pool[ip_str]->client_socket_addr = _client_socket_addr;
						 printf("--- info --- client %s is register on server.\n",ip_str.c_str());
					 }
				break;
			 }
			 push_message(message,ip_str);
		 }
		 else
			 printf("Error %i \n", WSAGetLastError());
	}
}

void server_udp::push_message(message_ext *message, std::string ip_str)
{
	EnterCriticalSection(&_server_critical_section);
	_clients_messages_pool[ip_str]->messages.push_back((*message));
	LeaveCriticalSection(&_server_critical_section);
	 Vector3d *vPosition = (Vector3d*)(message->data);
	 printf("from %s:UDP%u : %f, %f, %f . \n",inet_ntoa(_client_socket_addr.sin_addr),ntohs(_client_socket_addr.sin_port),vPosition->x,vPosition->y,vPosition->z);
}

void server_udp::_update_sender()
{
	while(true)
	{
		std::map<std::string,client_params*>::iterator _clients_iterator = _clients_messages_pool.begin();
		while(_clients_iterator != _clients_messages_pool.end())
		{
			unsigned int message_index = 0;
			EnterCriticalSection(&_server_critical_section);
			std::vector<message_ext>::iterator _message_iterator = _clients_iterator->second->messages.begin();
			while(_message_iterator != _clients_iterator->second->messages.end())
			{
				int socket_result = sendto(_socket_id, (char*)&(*_message_iterator), (*_message_iterator).header.message_size + sizeof(message_header), 0, (struct sockaddr *) &_clients_iterator->second->client_socket_addr, sizeof(_clients_iterator->second->client_socket_addr));
				Vector3d *temp = (Vector3d*)(*_message_iterator).data;
				++message_index;
				if(message_index > MESSAGES_COUNT_PER_TICK)
					break;
				if(socket_result < 0)
				{	
					printf("Error %i \n", WSAGetLastError());
				 continue;
				}
				_clients_iterator->second->messages.erase(_message_iterator);
				_message_iterator = _clients_iterator->second->messages.begin();
			}
			LeaveCriticalSection(&_server_critical_section);
			Sleep(OPTIMAL_TICK_COUNT);
			++_clients_iterator;
		}
	}
}

void server_udp::enable()
{
	_is_working = true;
	ResumeThread(_thread_listener_handle);
	ResumeThread(_thread_sender_handle);
}


void server_udp::disable()
{
	_is_working = false;
	SuspendThread(_thread_listener_handle);
	SuspendThread(_thread_sender_handle);
}