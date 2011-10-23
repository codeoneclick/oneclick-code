#ifndef CVIDEOCONTROLLER_H
#define CVIDEOCONTROLLER_H
#pragma once

#include <windows.h>
#include <vfw.h>
#pragma comment (lib,"vfw32.lib")

#define MAX_CAMERA_COUNT 10
#define CAMERA_TIME_LIMIT 3


class CVideoController
{
private :
	static CVideoController* m_controller;
	HWND m_hWndC; 
public :
	CVideoController();
	~CVideoController();
	static CVideoController* Instance();
	void TakeScreen();
};

#endif