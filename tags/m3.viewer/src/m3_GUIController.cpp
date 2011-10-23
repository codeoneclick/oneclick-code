#include "m3_GUIController.h"

void m3_GUIController::Load()
{
	_main_menu = new main_menu();
	_main_menu->Load("main_menu");
}

void m3_GUIController::Update()
{
	_main_menu->OnEvent();
}