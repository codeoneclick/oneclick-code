#ifndef CURLREQUEST_H
#define CURLREQUEST_H
#pragma once

#include<windows.h>
#include<Wininet.h>
#include<stdio.h>
#include<string.h>
#include<tchar.h>

class CURLRequest
{
public:
	enum E_PROTOCOL { HTTP = 0, HTTPS = 1 };
	enum E_METHOD { GET = 0, POST = 1 };

	CURLRequest();
	~CURLRequest();

	bool Connect();
	void Disconnect();

	bool Send();
	char *Recv();
	DWORD RecvSize();

	void SetProtocol( E_PROTOCOL _protocol );
	void SetMethod( E_METHOD _method );

	void SetURL( LPCTSTR _url );
	void SetSubURL( LPCTSTR _subUrl );
	void SetPostData( LPCTSTR _data );
	void SetHeader( LPCTSTR _header );

	void Release();

protected:

	bool OpenInternet( LPCTSTR _agent = TEXT("none") );
	void CloseInternet();
	bool OpenConnection( LPCTSTR _url );
	void CloseConnection();
	bool Send( LPCTSTR _method, LPCTSTR _subUrl, LPCTSTR _data );
	void CloseRequest();
	
	char *Recv( char *_buffer, DWORD _size );
	void CreateRecvBuffer( DWORD _size );

	DWORD GetError() const { return m_error; }
	bool CheckError( bool _test );
	void LPStrCopy( LPTSTR& _dest, LPCTSTR _source );

	static void __stdcall StatusCallback( HINTERNET _hInternet, DWORD_PTR _context, DWORD _internetStatus, LPVOID _statusInformation, DWORD _statusInformationLength );

	HINTERNET m_hInternet;
	HINTERNET m_hConnection;
	HINTERNET m_hRequest;

	INTERNET_STATUS_CALLBACK 	m_callback;

	DWORD     m_error;
	bool      m_useSSL;
	LPTSTR    m_url;
	LPTSTR    m_subUrl;
	LPTSTR	  m_postData;
	LPTSTR    m_header;
	LPTSTR    m_method;
	char     *m_recvBuffer;
	DWORD     m_recvBufferSize;

private :

	static const int k_DEFAULT_RECV_BUFFER_SIZE = 1024; 
};

#endif