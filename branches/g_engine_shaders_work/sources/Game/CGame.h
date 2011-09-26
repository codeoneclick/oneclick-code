#ifndef CGAME_H
#define CGAME_H
#include "../Core/CDeviceD3D.h"
#include "../Core/Input.h"
#include "../Core/Window.h"

class CGame : public core::Input, public Core::CWindow
{
private :
	MSG	m_systemMessage;
	bool m_isGameRun;
public :
	CGame();
	virtual void update();
	virtual void render();
	bool isGameRun() { return m_isGameRun; }
};

#endif