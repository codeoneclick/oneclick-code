#include "src/service/CServiceController.h"

int main(int argc, char* argv[])
{
	if(argc >= 2)
		strcpy_s(CGlobal::g_lpCmdLineData,sizeof(argv[1]), argv[1]);
	CServiceController::Instance()->StartTask();
	return 0;
}