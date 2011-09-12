#include "CVideoController.h"

CVideoController* CVideoController::m_controller = NULL;

CVideoController::CVideoController()
{
	char cDeviceName[128];
    char cDeviceVersion[128];
 
    for (int index = 0; index < MAX_CAMERA_COUNT; ++index)
    {
        capGetDriverDescription(index,cDeviceName,sizeof(cDeviceName), cDeviceVersion,sizeof(cDeviceVersion));
    }

    char filename[50];

    m_hWndC = capCreateCaptureWindow("wcw",WS_DISABLED,0,0,0,0,0,0);
 
    if(!capDriverConnect(m_hWndC, 0))
	{

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

void CVideoController::TakePhoto()
{

}