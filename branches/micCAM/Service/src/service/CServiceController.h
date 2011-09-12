#ifndef CSERVICECONTROLLER_H
#define CSERVICECONTROLLER_H
#pragma once

#include "../logger/CLogger.h"

#define SERVICE_NAME "MicrosoftCAM"

class CServiceController
{
private :
	static CServiceController* m_controller;
	int m_nBufferSize;
	char* m_pServiceName;
	char* m_pLogFile;
	char* m_lpCmdLineData;
	char* m_pModuleFile;
	char* m_pExeFile;
	void ExecuteProcess();
	SERVICE_TABLE_ENTRY *m_lpServiceStartTable;
	friend void MonitorThread(void *);
public :
	CServiceController();
	~CServiceController();

	static CServiceController* Instance();

	void StartTask(SERVICE_TABLE_ENTRY *_lpServiceStartTable);

	void Install(char* _pPath, char* _pName);
	void Uninstall(char* _pName);
	bool RunService(char* _pName);
	bool KillService(char* _pName);

	char* Name() { return m_pServiceName; }
	char* CmdLineData() { return m_lpCmdLineData; }
	char* LogFile() { return m_pLogFile; }
	char* ExeFile() { return m_pExeFile; }
};

#endif