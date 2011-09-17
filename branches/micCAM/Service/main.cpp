#include "src/service/CServiceController.h"

int main(int argc, _TCHAR* argv[])
{
	if(argc >= 2)
		strcpy(CGlobal::g_lpCmdLineData, argv[1]);
	CServiceController::Instance()->StartTask();
	return 0;
}