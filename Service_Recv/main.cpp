#include"src/network/CNetworkController.h"

int main(int argc, char* argv[])
{
	CNetworkController::Instance()->Start();
	while( true )
	{
		CNetworkController::Instance()->Update();
	}

	return 0;
}

