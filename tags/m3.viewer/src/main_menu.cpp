#include "main_menu.h"

main_menu::main_menu()
{
}

void main_menu::Load(std::string name)
{
	m3_GUIEntity* _btnNext = new m3_GUIEntity();
	_btnNext->width = 50;
	_btnNext->height = 25;
	_btnNext->x = 0 + 10;
	_btnNext->y = WINDOW_HEIGHT/2;
	_btnNext->command = "btnNext";
	_btnNext->SetTexture("Content\\ui\\btn_prev.dds");
	_btnNext->visible = true;
	_elementsContainer.push_back(_btnNext);

	m3_GUIEntity* _btnPrev = new m3_GUIEntity();
	_btnPrev->width = 50;
	_btnPrev->height = 25;
	_btnPrev->x = WINDOW_WIDTH - 10 - _btnPrev->width;
	_btnPrev->y = WINDOW_HEIGHT/2;
	_btnPrev->command = "btnPrev";
	_btnPrev->SetTexture("Content\\ui\\btn_next.dds");
	_btnPrev->visible = true;
	_elementsContainer.push_back(_btnPrev);

	m3_GUIEntity* _btnLight = new m3_GUIEntity();
	_btnLight->width = 200;
	_btnLight->height = 50;
	_btnLight->x = WINDOW_WIDTH - 10 - _btnLight->width;
	_btnLight->y = WINDOW_HEIGHT - _btnLight->height*3;
	_btnLight->command = "btnLight";
	_btnLight->SetTexture("Content\\ui\\btn_light.dds");
	_btnLight->visible = false;
	_elementsContainer.push_back(_btnLight);

	m3_GUIEntity* _btnNormal = new m3_GUIEntity();
	_btnNormal->width = 200;
	_btnNormal->height = 50;
	_btnNormal->x = WINDOW_WIDTH - 10 - _btnNormal->width;
	_btnNormal->y =  WINDOW_HEIGHT - _btnNormal->height*2;
	_btnNormal->command = "btnNormal";
	_btnNormal->SetTexture("Content\\ui\\btn_normal.dds");
	_btnNormal->visible = false;
	_elementsContainer.push_back(_btnNormal);

	m3_GUIEntity* _btnExit = new m3_GUIEntity();
	_btnExit->width = 200;
	_btnExit->height = 50;
	_btnExit->x = WINDOW_WIDTH - 10 - _btnExit->width;
	_btnExit->y = WINDOW_HEIGHT - _btnExit->height;
	_btnExit->command = "btnExit";
	_btnExit->SetTexture("Content\\ui\\btn_exit.dds");
	_btnExit->visible = false;
	_elementsContainer.push_back(_btnExit);


	m3_GUIEntity* _btnExporToObj = new m3_GUIEntity();
	_btnExporToObj->width = 200;
	_btnExporToObj->height = 50;
	_btnExporToObj->x = 0 + 10;
	_btnExporToObj->y = WINDOW_HEIGHT - _btnExit->height*2;
	_btnExporToObj->command = "btnExportToObj";
	_btnExporToObj->SetTexture("Content\\ui\\btn_export_obj.dds");
	_btnExporToObj->visible = false;
	_elementsContainer.push_back(_btnExporToObj);

	m3_Core::GetGUI()->AddMenu(name,_elementsContainer);
}

void main_menu::OnEvent()
{
	std::string command = m3_Core::GetGUI()->GetCommand();
	if(command == "btnNext")
	{
		m3_Input::meshIndex--;
	}
	else if(command == "btnPrev")
	{
		m3_Input::meshIndex++;
	}
	else if(command == "btnLight")
	{
		m3_Input::enableLight = !m3_Input::enableLight;
	}
	else if(command == "btnNormal")
	{
		m3_Input::enableNormal = !m3_Input::enableNormal;
	}
	else if(command == "btnExit")
	{
		m3_Input::exitEvent = true;
	}
	else if(command == "btnExportToObj")
	{
		m3_Input::saveToObj = true;
	}
}