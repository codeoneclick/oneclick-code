#include "src/service/CServiceController.h"

/*void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
void WINAPI ServiceHandler(DWORD fdwControl);

SERVICE_TABLE_ENTRY	lpServiceStartTable[] = 
{
	{CServiceController::Instance()->Name(), ServiceMain},
	{NULL, NULL}
};

SERVICE_STATUS_HANDLE hServiceStatusHandle; 
SERVICE_STATUS ServiceStatus; */

int main(int argc, _TCHAR* argv[])
{
	if(argc >= 2)
		strcpy(CServiceController::Instance()->CmdLineData(), argv[1]);
	CServiceController::Instance()->StartTask();
	return 0;
}
/*
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	DWORD   status = 0; 
    DWORD   specificError = 0xfffffff; 
 
    ServiceStatus.dwServiceType        = SERVICE_WIN32; 
    ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
    ServiceStatus.dwWin32ExitCode      = 0; 
    ServiceStatus.dwServiceSpecificExitCode = 0; 
    ServiceStatus.dwCheckPoint         = 0; 
    ServiceStatus.dwWaitHint           = 0; 
 
    hServiceStatusHandle = RegisterServiceCtrlHandler(CServiceController::Instance()->Name(), ServiceHandler); 
    if (hServiceStatusHandle==0) 
    {
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "RegisterServiceCtrlHandler failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CServiceController::Instance()->LogFile(), pTemp);
        return; 
    } 
 
    ServiceStatus.dwCurrentState       = SERVICE_RUNNING; 
    ServiceStatus.dwCheckPoint         = 0; 
    ServiceStatus.dwWaitHint           = 0;  
    if(!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) 
    { 
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CServiceController::Instance()->LogFile(), pTemp);
    } 
}

void WINAPI ServiceHandler(DWORD fdwControl)
{
	switch(fdwControl) 
	{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			//ProcessStarted = FALSE;
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
			ServiceStatus.dwCheckPoint    = 0; 
			ServiceStatus.dwWaitHint      = 0;
			break; 
		case SERVICE_CONTROL_PAUSE:
			ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
			break;
		case SERVICE_CONTROL_CONTINUE:
			ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
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
				sprintf(pTemp,  "Unrecognized opcode %d\n", fdwControl);
				CLogger::Instance()->Write(CServiceController::Instance()->LogFile(), pTemp);
			}
	};
    if (!SetServiceStatus(hServiceStatusHandle,  &ServiceStatus)) 
	{ 
		long nError = GetLastError();
		char pTemp[121];
		sprintf(pTemp, "SetServiceStatus failed, error code = %d\n", nError);
		CLogger::Instance()->Write(CServiceController::Instance()->LogFile(), pTemp);
    } 
}
*/