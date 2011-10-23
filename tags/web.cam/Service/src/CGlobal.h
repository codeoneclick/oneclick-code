#ifndef CGLOBAL_H
#define CGLOBAL_H

#include<windows.h>

#define BUFFER_SIZE 256

class CGlobal
{
public :
	static char* g_pServiceName;
	static char* g_pLogFile;
	static char* g_lpCmdLineData;
	static char* g_pModuleFile;
	static char* g_pExeFile;
	static char* g_pScreenFile;

	static void Release();
};

#endif
