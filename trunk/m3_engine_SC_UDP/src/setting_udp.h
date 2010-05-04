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

#define MESSAGE_BUFFER_MAX_SIZE 1024
#define SERVER_PORT 6633
#define SERVER_IP "127.0.0.1"
#define OPTIMAL_TICK_COUNT 33
#define CRITICAL_TICK_COUNT 66

struct message_header
{
	unsigned int message_id;
	unsigned int message_type;
	unsigned int message_size;
};


#endif