#pragma once
#ifndef _SERVER_UDP_H_
#define _SERVER_UDP_H_

#include "setting_udp.h"

#include "Vector3d.h"

DWORD __stdcall server_listener_thread(void* in_value);
DWORD __stdcall server_sender_thread(void* in_value);

class server_udp
{
private :
	unsigned int _socket_id;
	struct sockaddr_in _server_socket_addr;
	struct sockaddr_in _client_socket_addr;
	char *_message_buffer;
	message_header *_message_ptr;
	bool _is_working;
	HANDLE _thread_listener_handle;
	HANDLE _thread_sender_handle;
public :
	server_udp();
	void init();
	void enable();
	void disable();
	void _update_listener();
	void _update_sender();
	__forceinline bool is_enable() { return _is_working; }
};

#endif