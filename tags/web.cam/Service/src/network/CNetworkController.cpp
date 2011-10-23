#include "CNetworkController.h"
#include "../logger/CLogger.h"
#include "../CGlobal.h"

CNetworkController* CNetworkController::m_controller = NULL;

CNetworkController::CNetworkController()
{

}

CNetworkController::~CNetworkController()
{

}

CNetworkController* CNetworkController::Instance()
{
	if(m_controller == NULL)
	{
		m_controller = new CNetworkController();
	}
	return m_controller;
}

bool CNetworkController::Connect()
{
	 WSADATA wsaData;
     if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	 {
		 long nError = WSAGetLastError();
		 char pTemp[128];
		 sprintf_s(pTemp, "Error at WSAStartup, error code = %d\n", nError);
		 CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		 return false;
	 }

	 m_host = gethostbyname(k_SERVER_IP); 

	 if(m_host == NULL) 
	 {
		 WSACleanup();
		 long nError = WSAGetLastError();
		 char pTemp[128];
		 sprintf_s(pTemp, "No host, error code = %d\n", nError);
		 CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		 return false;
	 }

	 m_serverSocket_addr.sin_family = m_host->h_addrtype;
     memcpy((char *) &m_serverSocket_addr.sin_addr.s_addr, m_host->h_addr_list[0], m_host->h_length);
     m_serverSocket_addr.sin_port = htons(k_SERVER_PORT);

	 m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	 if(m_socket == INVALID_SOCKET)    
	 {
		 WSACleanup();
		 long nError = WSAGetLastError();
		 char pTemp[128];
		 sprintf_s(pTemp, "Cannot open socket, error code = %d\n", nError);
		 CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		 return false;
	 }
	 else
	 {
		char pTemp[128];
		sprintf_s(pTemp, "Socket open = %d\n", m_socket);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		return true;
	 }
	 return true;
}

bool CNetworkController::Send(const char *_data, unsigned int _size)
{
	unsigned int size = _size + k_HEADER_SIZE;
	char pSizeStr[128];
	std::string pMessage;
	sprintf_s(pSizeStr, 128, "%d", _size);
	pMessage = pSizeStr;
	while( pMessage.length() < k_HEADER_SIZE )
	{
		pMessage += "*";
	}

	pMessage += _data;

	if(sendto(m_socket, pMessage.c_str(), size, 0, (struct sockaddr *) &m_serverSocket_addr, sizeof(m_serverSocket_addr)) < 0)
	{	
		long nError = WSAGetLastError();
		char pTemp[128];
	    sprintf_s(pTemp, "Sending error, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		return false;
	}
	else
	{
		char pTemp[128];
		sprintf_s(pTemp, "Sending data = %s, size = %d\n", pMessage.c_str(), size);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		return true;
	}
	return true;
}

void CNetworkController::Disconnect()
{
	closesocket(m_socket);
}