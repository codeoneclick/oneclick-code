#include "CURLRequest.h"
#include <string.h>
#include <tchar.h>
#pragma comment(lib,"wininet")


CURLRequest::CURLRequest()
: m_hInternet(NULL),
  m_hConnection(NULL),
  m_hRequest(NULL),
  m_url(NULL),
  m_subUrl(NULL),
  m_postData(NULL),
  m_method(NULL),
  m_header(NULL),
  m_recvBuffer(NULL),
  m_recvBufferSize(0),
  m_useSSL(false),
  m_error(0)
{
	SetHeader(TEXT("Content-Type: application/x-www-form-urlencoded\r\n"));
}

CURLRequest::~CURLRequest()
{
	Release();
	SetHeader(NULL);
}

void CURLRequest::Release()
{
	if( m_url != NULL )
	{
		delete m_url;
		m_url = NULL;
	}
	if( m_subUrl != NULL )
	{
		delete m_subUrl;
		m_subUrl = NULL;
	}
	if( m_postData != NULL )
	{
		delete m_postData;
		m_postData = NULL;
	}
	if( m_method != NULL )
	{
		delete m_method;
		m_method = NULL;
	}
	if( m_header != NULL )
	{
		delete m_header;
		m_header = NULL;
	}
	if( m_recvBuffer != NULL )
	{
		delete m_recvBuffer;
		m_recvBuffer = NULL;
	}
}

void CURLRequest::LPStrCopy ( LPTSTR& _dest, LPCTSTR _source )
{
	if( _dest != NULL )
	{
		delete _dest;
		_dest = NULL;
	}

	if ( _source == NULL ) 
	{
		_dest = NULL;
	}
	else 
	{
		_dest = new TCHAR[_tcslen(_source) + 1];
		_tcscpy( _dest, _source );
	}
}

void CURLRequest::SetHeader( LPCTSTR _header )
{
	LPStrCopy( m_header,_header );
}

void CURLRequest::SetProtocol( E_PROTOCOL _protocol )
{
	if( _protocol == CURLRequest::E_PROTOCOL::HTTP )
	{
		m_useSSL = false;
	}
	else if( _protocol == CURLRequest::E_PROTOCOL::HTTPS )
	{
		m_useSSL = true;
	}
}

void CURLRequest::SetMethod( E_METHOD _method )
{
	if( _method == CURLRequest::E_METHOD::GET )
	{
		LPStrCopy( m_method, "GET" );
	}
	else if( _method == CURLRequest::E_METHOD::POST )
	{
		LPStrCopy( m_method, "POST" );
	}
}

void CURLRequest::SetURL( LPCTSTR _url )
{
	LPStrCopy( m_url, _url );
}

void CURLRequest::SetSubURL( LPCTSTR _subUrl )
{
	LPStrCopy( m_subUrl, _subUrl );
}

void CURLRequest::SetPostData( LPCTSTR _data )
{
	LPStrCopy( m_postData, _data );
}

bool CURLRequest::CheckError(bool _test)
{
	if (_test == false) 
	{
		m_error = ::GetLastError();
	}
	return _test;
}

bool CURLRequest::OpenInternet(LPCTSTR _agent)
{
	if (m_hInternet == NULL)
	{
		m_hInternet = ::InternetOpen( _agent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	}

	m_callback = InternetSetStatusCallback( m_hInternet, (INTERNET_STATUS_CALLBACK)StatusCallback );

	return CheckError(m_hInternet != NULL);
}

void CURLRequest::CloseInternet()
{
	CloseConnection();
	
	if (m_hInternet) 
	{
	    ::InternetCloseHandle(m_hInternet);
	}
	m_hInternet = NULL;
}

bool CURLRequest::OpenConnection( LPCTSTR _url )
{
	if (OpenInternet() && m_hConnection == NULL)
	{
		m_hConnection = ::InternetConnect( m_hInternet, _url ? _url:TEXT("localhost"), m_useSSL? INTERNET_DEFAULT_HTTPS_PORT: INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1u);
	}
	return CheckError(m_hConnection != NULL);
}

void CURLRequest::CloseConnection ()
{
	CloseRequest();

	if (m_hConnection)
	{
		::InternetCloseHandle(m_hConnection);
	}
	m_hConnection = NULL;
}

bool CURLRequest::Send( LPCTSTR _method, LPCTSTR _subUrl, LPCTSTR _postData )
{
	if (m_hConnection != NULL) 
	{
		CloseRequest();

		LPCTSTR AcceptTypes[] = { TEXT("*/*"), NULL }; 
		m_hRequest = ::HttpOpenRequest( m_hConnection, _method, _subUrl, NULL, NULL, AcceptTypes, (m_useSSL? INTERNET_FLAG_SECURE|INTERNET_FLAG_IGNORE_CERT_CN_INVALID: 0) | INTERNET_FLAG_KEEP_CONNECTION, 1);

		if (m_hRequest != NULL) 
		{
			if (::HttpSendRequest( m_hRequest, m_header, -1, (LPVOID)_postData, _postData ? _tcslen(_postData): 0) == FALSE)
			{
				CheckError(false);
				CloseRequest();
				return false;
			}
		}
	}

	return CheckError(m_hRequest != NULL);
}

void CURLRequest::CloseRequest()
{
	if (m_hRequest)
	{
		::InternetCloseHandle(m_hRequest);
	}
	m_hRequest = NULL;
}																			   

char *CURLRequest::Recv( char *_buffer, DWORD _size )
{
	if (m_hRequest) 
	{
		DWORD readSize = 0;
		bool bRead = ::InternetReadFile( m_hRequest, _buffer, _size, &readSize ) != FALSE;
		_buffer[readSize] = 0;
		return CheckError(bRead) && readSize ? _buffer : NULL;
	}
	return NULL;
}

DWORD CURLRequest::RecvSize()
{
	if (m_hRequest) 
	{
		DWORD dataSize = 0;
		DWORD lengthDataSize = sizeof(dataSize);

		BOOL bQuery = ::HttpQueryInfo( m_hRequest, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &dataSize, &lengthDataSize, NULL );
		
		return bQuery ? dataSize : k_DEFAULT_RECV_BUFFER_SIZE;
	}
	return 0;
}

char *CURLRequest::Recv()
{
	DWORD size = RecvSize();
	CreateRecvBuffer( size );	
	return Recv( m_recvBuffer, size ? size : m_recvBufferSize );
}

void CURLRequest::CreateRecvBuffer( DWORD _size )
{
	if ( _size > m_recvBufferSize ) 
	{
		delete m_recvBuffer;
		m_recvBuffer = new char[(m_recvBufferSize = _size) + 1];
	}
}

bool CURLRequest::Connect()
{
	return OpenConnection( m_url );
}

void CURLRequest::Disconnect()
{
	return CloseConnection();
}

bool CURLRequest::Send()
{
	return Send(m_method, m_subUrl, m_postData );
}

void __stdcall CURLRequest::StatusCallback( HINTERNET _hInternet, DWORD_PTR _context, DWORD _internetStatus, LPVOID _statusInformation, DWORD _statusInformationLength )
{
	 switch(_internetStatus)
     {
        case INTERNET_STATUS_COOKIE_SENT:
            printf("Status: Cookie found and will be sent with request\n");
            break;
            
        case INTERNET_STATUS_COOKIE_RECEIVED:
            printf("Status: Cookie Received\n");
            break;
            
        case INTERNET_STATUS_COOKIE_HISTORY:
            printf("Status: Cookie History\n");
            break;
            
        case INTERNET_STATUS_CLOSING_CONNECTION:
            printf("Status: Closing Connection\n");
            break;
            
        case INTERNET_STATUS_CONNECTED_TO_SERVER:
            printf("Status: Connected to Server\n");
            break;
            
        case INTERNET_STATUS_CONNECTING_TO_SERVER:
            printf("Status: Connecting to Server\n");
            break;
            
        case INTERNET_STATUS_CONNECTION_CLOSED:
            printf("Status: Connection Closed\n");
            break;
            
        case INTERNET_STATUS_HANDLE_CLOSING:
            printf("Status: Handle Closing\n");
            break;
            
        case INTERNET_STATUS_HANDLE_CREATED:
            printf("Handle %x created\n", ((LPINTERNET_ASYNC_RESULT)_statusInformation)->dwResult);

            break;
            
        case INTERNET_STATUS_INTERMEDIATE_RESPONSE:
            printf("Status: Intermediate response\n");
            break;
            
        case INTERNET_STATUS_RECEIVING_RESPONSE:
            printf("Status: Receiving Response\n");    
            break;
            
        case INTERNET_STATUS_RESPONSE_RECEIVED:
            printf("Status: Response Received (%d Bytes)\n", *((LPDWORD)_statusInformation));
            break;
            
        case INTERNET_STATUS_REDIRECT:
            printf("Status: Redirect\n");
            break;

        case INTERNET_STATUS_REQUEST_COMPLETE:
            printf("Status: Request complete\n");
            break;
            
        case INTERNET_STATUS_REQUEST_SENT:
            printf("Status: Request sent (%d Bytes)\n", *((LPDWORD)_statusInformation));
            break;
            
        case INTERNET_STATUS_DETECTING_PROXY:
            printf("Status: Detecting Proxy\n");
            break;            
            
        case INTERNET_STATUS_RESOLVING_NAME:
            printf("Status: Resolving Name\n");
            break;
            
        case INTERNET_STATUS_NAME_RESOLVED:
            printf("Status: Name Resolved\n");
            break;
            
        case INTERNET_STATUS_SENDING_REQUEST:
            printf("Status: Sending request\n");
            break;
            
        case INTERNET_STATUS_STATE_CHANGE:
            printf("Status: State Change\n");
            break;
            
        case INTERNET_STATUS_P3P_HEADER:
            printf("Status: Received P3P header\n");
            break;
            
        default:
            printf ("Status: Unknown (%d)\n", _internetStatus);
            break;
    }
}
