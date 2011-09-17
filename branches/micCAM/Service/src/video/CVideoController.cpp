#include "CVideoController.h"
#include "../logger/CLogger.h"
#include "../CGlobal.h"

CVideoController* CVideoController::m_controller = NULL;

CVideoController::CVideoController()
{
	/*char cDeviceName[128];
    char cDeviceVersion[128];
 
    for (int index = 0; index < MAX_CAMERA_COUNT; ++index)
    {
        capGetDriverDescription(index,cDeviceName,sizeof(cDeviceName), cDeviceVersion,sizeof(cDeviceVersion));
    }*/

    //char filename[50];
	//sprintf_s(CGlobal::g_pScreenFile,sizeof(filename),"screen.bmp");

    m_hWndC = capCreateCaptureWindow("webCamHandle",WS_DISABLED,0,0,0,0,0,0);
 
    if(!capDriverConnect(m_hWndC, 0))
	{
		long nError = GetLastError();
		char pTemp[128];
		sprintf(pTemp, "Driver Connect, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
	}

    CAPTUREPARMS CaptureParms;
    capCaptureGetSetup(m_hWndC, &CaptureParms, sizeof(CaptureParms));   
    CaptureParms.fLimitEnabled = true;
    CaptureParms.wTimeLimit = CAMERA_TIME_LIMIT;
    CaptureParms.fCaptureAudio = false;
    capCaptureSetSetup(m_hWndC, &CaptureParms, sizeof(CAPTUREPARMS));
    capCaptureSequenceNoFile(m_hWndC);
}

CVideoController::~CVideoController()
{

}

CVideoController *CVideoController::Instance()
{
	if ( m_controller == NULL )
	{
		m_controller = new CVideoController();
	}

	return m_controller;
}

void CVideoController::TakeScreen()
{
	 if(!capGrabFrameNoStop(m_hWndC))
     {
		long nError = GetLastError();
		char pTemp[128];
		sprintf(pTemp, "Grab Frame, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
     }

	 if(!capFileSaveDIB(m_hWndC,CGlobal::g_pScreenFile))
     {
		long nError = GetLastError();
		char pTemp[128];
		sprintf(pTemp, "File Save, error code = %d\n", nError);
		CLogger::Instance()->Write(CGlobal::g_pLogFile, pTemp);
     }
}