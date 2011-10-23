#include"CURLController.h"

CURLController* CURLController::m_controller = NULL;

CURLController::CURLController()
{

}
CURLController::~CURLController()
{

}

CURLController* CURLController::Instance()
{
	if( m_controller == NULL )
	{
		m_controller = new CURLController();
		return m_controller;
	}
	else
	{
		return m_controller;
	}
}

void CURLController::LPStrCopy ( LPTSTR& _dest, std::string _source )
{
	if( _dest != NULL )
	{
		delete _dest;
		_dest = NULL;
	}

	if ( _source.c_str() == NULL ) 
	{
		_dest = NULL;
	}
	else 
	{
		_dest = new TCHAR[_tcslen(_source.c_str()) + 1];
		_tcscpy( _dest, _source.c_str() );
	}
}

void CURLController::Send(std::string _name, std::string _protocol, std::string _method, std::string _url, std::string _subUrl, std::string _data)
{
	SURLRequestSend *requestToSend = new SURLRequestSend();
	requestToSend->s_name = _name;
	requestToSend->s_protocol = _protocol;
	requestToSend->s_method = _method;
	LPStrCopy(requestToSend->s_url,_url);
	LPStrCopy(requestToSend->s_subUrl,_subUrl);
	LPStrCopy(requestToSend->s_data,_data);

	if( m_requestToSend.find(_name) == m_requestToSend.end() )
	{
		m_requestToSend[_name] = requestToSend;
	}
}

char* CURLController::Recv(std::string _name)
{
	return NULL;
}

void CURLController::Update()
{
	std::map<std::string,SURLRequestSend*>::iterator itBegin = m_requestToSend.begin();
	std::map<std::string,SURLRequestSend*>::iterator itEnd = m_requestToSend.end();

	while(itBegin != itEnd)
	{
		SURLRequestSend *requestToSend = (*itBegin).second;
		CURLRequest request;
		SURLRequestRecv *requestToRecv = new SURLRequestRecv();
		request.SetURL(requestToSend->s_url);
		request.SetSubURL(requestToSend->s_subUrl);
		request.SetPostData(requestToSend->s_data);
		if( requestToSend->s_protocol == "HTTPS" )
		{
			request.SetProtocol(CURLRequest::E_PROTOCOL::HTTPS);
		}
		else if( requestToSend->s_protocol == "HTTP" )
		{
			request.SetProtocol(CURLRequest::E_PROTOCOL::HTTP);
		}
		if( requestToSend->s_method == "GET" )
		{
			request.SetMethod(CURLRequest::E_METHOD::GET);
		}
		else if( requestToSend->s_method == "POST" )
		{
			request.SetMethod(CURLRequest::E_METHOD::POST);
		}
		
		if( !request.Connect() )
		{
			requestToRecv->s_data = "ERROR";
			requestToRecv->s_error = 1;
		}

		if( !request.Send() )
		{
			requestToRecv->s_data = "ERROR";
			requestToRecv->s_error = 1;
		}

		requestToRecv->s_size = request.RecvSize();
		requestToRecv->s_data = new char[requestToRecv->s_size];
		memcpy(requestToRecv->s_data, request.Recv(), requestToRecv->s_size );

		m_requestToRecv[requestToSend->s_name] = requestToRecv;
		request.Disconnect();

		delete requestToSend;

		itBegin++;
	}
	m_requestToSend.clear();
}