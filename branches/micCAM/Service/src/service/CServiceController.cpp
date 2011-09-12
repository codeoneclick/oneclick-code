#include "CServiceController.h"

void MonitorThread(void*)
{
	while(true)
	{

	}
}

CServiceController* CServiceController::m_controller = NULL;

CServiceController::CServiceController()
{
	m_nBufferSize = 256;
	m_pServiceName = new char[m_nBufferSize + 1];
	m_pLogFile = new char[m_nBufferSize + 1];
	m_lpCmdLineData = new char[m_nBufferSize + 1];
	m_pModuleFile = new char[m_nBufferSize + 1];
	m_pExeFile = new char[m_nBufferSize + 1];
}

CServiceController::~CServiceController()
{
	if( m_pServiceName != NULL)
	{
		delete m_pServiceName;
		m_pServiceName = NULL;
	}

	if( m_pLogFile != NULL)
	{
		delete m_pLogFile;
		m_pLogFile = NULL;
	}

	if( m_lpCmdLineData != NULL)
	{
		delete m_lpCmdLineData;
		m_lpCmdLineData = NULL;
	}

	if( m_pModuleFile != NULL)
	{
		delete m_pModuleFile;
		m_pModuleFile = NULL;
	}
}

CServiceController* CServiceController::Instance()
{
	if( m_controller == NULL )
	{
		m_controller = new CServiceController();
	}

	return m_controller;
}


void CServiceController::StartTask(SERVICE_TABLE_ENTRY *_lpServiceStartTable)
{
	m_lpServiceStartTable = _lpServiceStartTable;
	DWORD dwSize = GetModuleFileName(NULL, m_pModuleFile, m_nBufferSize);
	m_pModuleFile[dwSize] = 0;
	if(dwSize > 4 && m_pModuleFile[dwSize - 4] == '.')
	{
		sprintf(m_pExeFile,"%s",m_pModuleFile);
		m_pModuleFile[dwSize - 4] = 0;
		sprintf(m_pLogFile,"%s.log",m_pModuleFile);
	}
	strcpy(m_pServiceName,SERVICE_NAME);

	if(_stricmp("-i",m_lpCmdLineData) == 0 || _stricmp("-I",m_lpCmdLineData) == 0)
	{
		Install(m_pExeFile, m_pServiceName);
	}
	else if(_stricmp("-k",m_lpCmdLineData) == 0 || _stricmp("-K",m_lpCmdLineData) == 0)
	{
		KillService(m_pServiceName);
	}
	else if(_stricmp("-u",m_lpCmdLineData) == 0 || _stricmp("-U",m_lpCmdLineData) == 0)
	{
		Uninstall(m_pServiceName);
	}
	else if(_stricmp("-s",m_lpCmdLineData) == 0 || _stricmp("-S",m_lpCmdLineData) == 0)
	{
		RunService(m_pServiceName);
	}
	else
	{
		ExecuteProcess();
	}
}


void CServiceController::Install(char* _pPath, char* _pName)
{  
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(m_pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = CreateService
		( 
			schSCManager,	/* SCManager database      */ 
			_pName,			/* name of service         */ 
			_pName,			/* service name to display */ 
			SERVICE_ALL_ACCESS,        /* desired access          */ 
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , /* service type            */ 
			SERVICE_AUTO_START,      /* start type              */ 
			SERVICE_ERROR_NORMAL,      /* error control type      */ 
			_pPath,			/* service's binary        */ 
			NULL,                      /* no load ordering group  */ 
			NULL,                      /* no tag identifier       */ 
			NULL,                      /* no dependencies         */ 
			NULL,                      /* LocalSystem account     */ 
			NULL
		);                     /* no password             */ 
		if (schService==0) 
		{
			long nError =  GetLastError();
			char pTemp[121];
			sprintf(pTemp, "Failed to create service %s, error code = %d\n", _pName, nError);
			CLogger::Instance()->Write(m_pLogFile, pTemp);
		}
		else
		{
			char pTemp[121];
			sprintf(pTemp, "Service %s installed\n", _pName);
			CLogger::Instance()->Write(m_pLogFile, pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);
	}	
}

void CServiceController::Uninstall(char* _pName)
{
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(m_pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, _pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf(pTemp, "OpenService failed, error code = %d\n", nError);
			CLogger::Instance()->Write(m_pLogFile, pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				char pTemp[121];
				sprintf(pTemp, "Failed to delete service %s\n", _pName);
				CLogger::Instance()->Write(m_pLogFile, pTemp);
			}
			else 
			{
				char pTemp[121];
				sprintf(pTemp, "Service %s removed\n",_pName);
				CLogger::Instance()->Write(m_pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
	}
	DeleteFile(m_pLogFile);
}


bool CServiceController::RunService(char* _pName) 
{ 
	// run service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(m_pLogFile, pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, _pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf(pTemp, "OpenService failed, error code = %d\n", nError);
			CLogger::Instance()->Write(m_pLogFile, pTemp);
		}
		else
		{
			// call StartService to run the service
			if(StartService(schService, 0, (const char**)NULL))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			else
			{
				long nError = GetLastError();
				char pTemp[121];
				sprintf(pTemp, "StartService failed, error code = %d\n", nError);
				CLogger::Instance()->Write(m_pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}

bool CServiceController::KillService(char* _pName) 
{ 
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(m_pLogFile, pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, _pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf(pTemp, "OpenService failed, error code = %d\n", nError);
			CLogger::Instance()->Write(m_pLogFile, pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			else
			{
				long nError = GetLastError();
				char pTemp[121];
				sprintf(pTemp, "ControlService failed, error code = %d\n", nError);
				CLogger::Instance()->Write(m_pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}

void  CServiceController::ExecuteProcess()
{
	if(_beginthread(MonitorThread, 0, NULL) == -1)
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "StartService failed, error code = %d\n", nError);
		CLogger::Instance()->Write(m_pLogFile, pTemp);
	}
	if(!StartServiceCtrlDispatcher(m_lpServiceStartTable))
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "StartServiceCtrlDispatcher failed, error code = %d\n", nError);
		CLogger::Instance()->Write(m_pLogFile, pTemp);
	}
}
