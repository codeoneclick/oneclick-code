#ifndef CLOGGER_H
#define CLOGGER_H
#pragma once

#include <process.h>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <winsvc.h>

class CLogger
{
private :
	static CLogger* m_logger;
	CRITICAL_SECTION m_ctiticalSection;
public :
	CLogger();
	~CLogger();
	static CLogger* Instance();
	void Write(char* _pFile, char* _pMsg);
};

#endif