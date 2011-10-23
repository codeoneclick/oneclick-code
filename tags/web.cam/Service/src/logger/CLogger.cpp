#include "CLogger.h"

CLogger* CLogger::m_logger = NULL;

CLogger::CLogger()
{
	::InitializeCriticalSection(&m_ctiticalSection);
}

CLogger::~CLogger()
{
	::DeleteCriticalSection(&m_ctiticalSection);
}

CLogger* CLogger::Instance()
{
	if ( m_logger == NULL )
	{
		m_logger = new CLogger();
	}

	return m_logger;
}

void CLogger::Write(char *_pFile, char *_pMsg)
{
	::EnterCriticalSection(&m_ctiticalSection);
	try
	{
		SYSTEMTIME systemTime;
		::GetLocalTime(&systemTime);
		FILE* pLog;
		fopen_s(&pLog, _pFile,"a");
		fprintf(pLog,"%02d/%02d/%04d, %02d:%02d:%02d\n    %s",systemTime.wMonth,systemTime.wDay,systemTime.wYear,systemTime.wHour,systemTime.wMinute,systemTime.wSecond,_pMsg); 
		fclose(pLog);
	} 
	catch(...) {}
	::LeaveCriticalSection(&m_ctiticalSection);
}