#include "CNetworkController.h"

CNetworkController* CNetworkController::m_controller = NULL;

CNetworkController::CNetworkController()
{
	m_buffer = new char[k_MESSAGE_SIZE];
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

bool CNetworkController::Start()
{
	 WSADATA wsaData;
     if(WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	 {
         printf("Error at WSAStartup\n");
		 return false;
	 }

	 if((m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)    
	 {
	    printf("Cannot open socket. Error %i \n",WSAGetLastError());
		WSACleanup();
		return false;
	 }
	 else
	 {
		printf("Socket open \n");
	 }

	  m_serverSocket_addr.sin_family = AF_INET;
	  m_serverSocket_addr.sin_addr.s_addr = inet_addr(k_SERVER_IP);
	  m_serverSocket_addr.sin_port = htons(k_SERVER_PORT);

	  if(bind(m_socket, (struct sockaddr *) &m_serverSocket_addr,sizeof(m_serverSocket_addr)) == SOCKET_ERROR)
	  {
	    printf("Cannot bind port. Error %i \n", WSAGetLastError());
		WSACleanup();
		closesocket(m_socket);
		return false;
	  }
	  else
	  {
		printf("Bind port \n");
	  }

	  printf("Ready  to listen... \n");
	  return true;
}

void CNetworkController::Update()
{
	struct sockaddr_in clientSocket_addr;
	int sockaddrSize = sizeof(clientSocket_addr);
	if(recvfrom(m_socket, m_buffer, k_MESSAGE_SIZE, 0,(struct sockaddr *) &clientSocket_addr, &sockaddrSize) > 0)
	{	
		char *pSizeBuffer = new char[k_HEADER_SIZE + 1];
		memcpy(pSizeBuffer,m_buffer,k_HEADER_SIZE);
		pSizeBuffer[k_HEADER_SIZE] = 0;
		std::string pSizeStrTemp = pSizeBuffer;
		std::string pSizeStr;
		for(int i = 0; i < pSizeStrTemp.length(); i++)
		{
			if(pSizeStrTemp[i] != '*')
			{
				pSizeStr += pSizeStrTemp[i];
			}
		}
		
		unsigned int size = (unsigned int)atoi(pSizeStr.c_str());
		char *pData = new char[size + 1];
		memcpy(pData, m_buffer + k_HEADER_SIZE, size);
		pData[size] = 0;
		printf(" %s \n",pData);
	}
}