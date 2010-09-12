#pragma once
#pragma comment(lib, "winmm.lib")
class gFps
{
public:
	float Fps;
	gFps();
	bool CalculateFrameRate();
};

gFps::gFps()
{
	this->Fps = 0;
}

bool gFps::CalculateFrameRate()
{
	static DWORD framesPerSecond = 0;	
	static DWORD lastTime = 0;			
	static char strFrameRate[50] = {0};		
	
	DWORD currentTime = GetTickCount();//timeGetTime() * 0.001f;
	++framesPerSecond;

	if(currentTime - lastTime > 1000 )
	{
		lastTime = currentTime;
		Fps = (float)framesPerSecond;
		framesPerSecond = 0;
		return true;
	}
	return false;
}