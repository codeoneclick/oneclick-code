#pragma once
#ifndef _SETTING_UDP_H_
#define _SETTING_UDP_H_

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")

#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "Vector3d.h"

#define MESSAGE_BUFFER_MAX_SIZE 1024
#define SERVER_PORT 6633
#define SERVER_IP "127.0.0.1"
#define OPTIMAL_TICK_COUNT 33
#define CRITICAL_TICK_COUNT 66
#define MESSAGES_COUNT_PER_TICK 8

#define CS_CONNECT 1024
#define CS_DISCONNECT 1025
#define CS_UPDATE_UNIT_ASPECT 1026

struct message_header
{
	unsigned int message_id;
	unsigned int message_type;
	unsigned int message_size;
};

struct message_ext
{	
	message_header header;
	char *data;
};

struct client_params
{
	std::string ip_str;
	struct sockaddr_in client_socket_addr;
	std::vector<message_ext> messages;
};


struct message_unit_aspect
{
	message_header header;
	Vector3d vPosition;
	Vector3d vRotation;
};

#endif