#include "CGlobal.h"

char* CGlobal::g_pServiceName = new char[BUFFER_SIZE + 1];
char* CGlobal::g_pLogFile = new char[BUFFER_SIZE + 1];
char* CGlobal::g_lpCmdLineData = new char[BUFFER_SIZE + 1];
char* CGlobal::g_pModuleFile = new char[BUFFER_SIZE + 1];
char* CGlobal::g_pExeFile = new char[BUFFER_SIZE + 1];
char* CGlobal::g_pScreenFile = new char[BUFFER_SIZE + 1];

void CGlobal::Release()
{
	if( g_pServiceName != NULL)
	{
		delete g_pServiceName;
		g_pServiceName = NULL;
	}

	if( g_pLogFile != NULL)
	{
		delete g_pLogFile;
		g_pLogFile = NULL;
	}

	if( g_lpCmdLineData != NULL)
	{
		delete g_lpCmdLineData;
		g_lpCmdLineData = NULL;
	}

	if( g_pModuleFile != NULL)
	{
		delete g_pModuleFile;
		g_pModuleFile = NULL;
	}
}