#ifndef CURLCONTROLLER_H
#define CURLCONTROLLER_H
#pragma once
#include<stdlib.h>
#include<map>
#include<string>
#include"CURLRequest.h"

class CURLController
{
public:

	CURLController();
	~CURLController();

	static CURLController* Instance();
	void Send(std::string _name, std::string _protocol, std::string _method, std::string _url, std::string _subUrl, std::string _data);
	char *Recv(std::string _name);

	void Update();

private :

	static CURLController* m_controller;

	struct SURLRequestSend
	{
		std::string s_name;
		std::string s_protocol;
		std::string s_method;
		LPTSTR s_url;
		LPTSTR s_subUrl;
		LPTSTR s_data;

		SURLRequestSend()
		{
			s_name = "";
			s_protocol = "";
			s_method = "";
			s_url = NULL;
			s_subUrl = NULL;
			s_data = NULL;
		}

		~SURLRequestSend()
		{
			if ( s_url != NULL )
			{
				delete s_url;
				s_url = NULL;
			}

			if ( s_subUrl != NULL )
			{
				delete s_subUrl;
				s_subUrl = NULL;
			}

			if ( s_data != NULL )
			{
				delete s_data;
				s_data = NULL;
			}
		}
	};

	struct SURLRequestRecv
	{
		char* s_data;
		DWORD s_size;
		DWORD s_error;

		SURLRequestRecv()
		{
			s_data = NULL;
			s_size = 0;
			s_error = 0;
		}
		
		~SURLRequestRecv()
		{
			if( s_data != NULL )
			{
				delete s_data;
				s_data = NULL;
			}
		}
	};
	
protected:

	void LPStrCopy ( LPTSTR& _dest, std::string _source );

	std::map<std::string, SURLRequestSend*> m_requestToSend;
	std::map<std::string, SURLRequestRecv*> m_requestToRecv;
};

#endif