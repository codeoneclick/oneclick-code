#pragma once
#ifndef _CLIENT_UDP_H_
#define _CLIENT_UDP_H_

#include "setting_udp.h"

DWORD __stdcall client_listener_thread(void* in_value);
DWORD __stdcall client_sender_thread(void* in_value);

class client_udp
{
private :
	unsigned int _socket_id;
	struct sockaddr_in _server_socket_addr;
	struct sockaddr_in _client_socket_addr;
	struct hostent *_host;
	char *_message_buffer;
	std::vector<message_ext> _message_pool;
	bool _is_working;
	HANDLE _thread_listener_handle;
	HANDLE _thread_sender_handle;
	CRITICAL_SECTION _client_critical_section;
	void _ping();
public :
	client_udp();
	void init();
	void enable();
	void disable();
	void _update_listener();
	void _update_sender();
	void send_message(message_ext *message);
	__forceinline bool is_enable() { return _is_working; }
};

#endif
