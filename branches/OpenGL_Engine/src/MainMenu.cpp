#include "MainMenu.h"

#include "Window.h"
#include "Core.h"
#include "Game.h"

#include "Editor.h"

MainMenu::MainMenu()
{

}

void MainMenu::Load(std::string value)
{
	GuiElementButton* _btnEditGround = new GuiElementButton();
	_btnEditGround->width = 64;
	_btnEditGround->height = 16;
	_btnEditGround->x = Window::currentWidth  - _btnEditGround->width - 5;
	_btnEditGround->y = Window::currentHeight/2;
	_btnEditGround->command = "btnEditGround";
	_btnEditGround->SetTexture("Content\\ui\\btn_heightmap_edit_main.dds");
	_btnEditGround->visible = true;
	_elementsContainer.push_back(_btnEditGround);

	GuiElementButton* _btnEditGrass = new GuiElementButton();
	_btnEditGrass->width = 64;
	_btnEditGrass->height = 16;
	_btnEditGrass->x = Window::currentWidth  - _btnEditGrass->width - 5;
	_btnEditGrass->y = Window::currentHeight/2 + 20;
	_btnEditGrass->command = "btnEditGrass";
	_btnEditGrass->SetTexture("Content\\ui\\button.dds");
	_btnEditGrass->visible = true;
	_elementsContainer.push_back(_btnEditGrass);

	GuiElementButton* _btnSave = new GuiElementButton();
	_btnSave->width = 64;
	_btnSave->height = 16;
	_btnSave->x = Window::currentWidth  - _btnSave->width - 5;
	_btnSave->y = Window::currentHeight/2 + 40;
	_btnSave->command = "btnSave";
	_btnSave->SetTexture("Content\\ui\\button.dds");
	_btnSave->visible = true;
	_elementsContainer.push_back(_btnSave);

	GuiElementButton* _btnExit = new GuiElementButton();
	_btnExit->width = 64;
	_btnExit->height = 16;
	_btnExit->x = Window::currentWidth  - _btnExit->width - 5;
	_btnExit->y = Window::currentHeight/2 + 60;
	_btnExit->command = "btnExit";
	_btnExit->SetTexture("Content\\ui\\button.dds");
	_btnExit->visible = true;
	_elementsContainer.push_back(_btnExit);

	GuiElementButton* _btnGroundHeightSimple = new GuiElementButton();
	_btnGroundHeightSimple->width = 64;
	_btnGroundHeightSimple->height = 16;
	_btnGroundHeightSimple->x = 0  - _btnGroundHeightSimple->width;
	_btnGroundHeightSimple->y = Window::currentHeight/2;
	_btnGroundHeightSimple->command = "btnGroundHeightSimple";
	_btnGroundHeightSimple->SetTexture("Content\\ui\\btn_heightmap_edit_rugged.dds");
	_btnGroundHeightSimple->visible = true;
	_elementsContainer.push_back(_btnGroundHeightSimple);

	GuiElementButton* _btnGroundHeightSmooth = new GuiElementButton();
	_btnGroundHeightSmooth->width = 64;
	_btnGroundHeightSmooth->height = 16;
	_btnGroundHeightSmooth->x = 0  - _btnGroundHeightSmooth->width;
	_btnGroundHeightSmooth->y = Window::currentHeight/2 + 20;
	_btnGroundHeightSmooth->command = "btnGroundHeightSmooth";
	_btnGroundHeightSmooth->SetTexture("Content\\ui\\btn_heightmap_edit_smooth.dds");
	_btnGroundHeightSmooth->visible = true;
	_elementsContainer.push_back(_btnGroundHeightSmooth);

	GuiElementButton* _btnGroundTexture = new GuiElementButton();
	_btnGroundTexture->width = 64;
	_btnGroundTexture->height = 16;
	_btnGroundTexture->x = 0  - _btnGroundTexture->width;
	_btnGroundTexture->y = Window::currentHeight/2 + 40;
	_btnGroundTexture->command = "btnGroundTexture";
	_btnGroundTexture->SetTexture("Content\\ui\\button.dds");
	_btnGroundTexture->visible = true;
	_elementsContainer.push_back(_btnGroundTexture);

	GuiElementButton* _btnBackMain = new GuiElementButton();
	_btnBackMain->width = 8;
	_btnBackMain->height = 8;
	_btnBackMain->x = 5;
	_btnBackMain->y = 5;
	_btnBackMain->command = "btnBackMain";
	_btnBackMain->SetTexture("Content\\ui\\button_back.dds");
	_btnBackMain->visible = true;
	_elementsContainer.push_back(_btnBackMain);

	GuiElementButton* _btnGroundInc = new GuiElementButton();
	_btnGroundInc->width = 32;
	_btnGroundInc->height = 32;
	_btnGroundInc->x =  Window::currentWidth/2  - _btnGroundInc->width - 5;
	_btnGroundInc->y = 0 - _btnGroundInc->height;
	_btnGroundInc->command = "btnGroundInc";
	_btnGroundInc->SetTexture("Content\\ui\\btn_heightmap_edit_up.dds");
	_btnGroundInc->visible = true;
	_elementsContainer.push_back(_btnGroundInc);

	GuiElementButton* _btnGroundDec = new GuiElementButton();
	_btnGroundDec->width = 32;
	_btnGroundDec->height = 32;
	_btnGroundDec->x = Window::currentWidth/2  + 5;
	_btnGroundDec->y = 0 - _btnGroundDec->height;
	_btnGroundDec->command = "btnGroundDec";
	_btnGroundDec->SetTexture("Content\\ui\\btn_heightmap_edit_down.dds");
	_btnGroundDec->visible = true;
	_elementsContainer.push_back(_btnGroundDec);

	Core::GetGuiController()->AddMenu(value, this);
	Core::GetGuiController()->SetCurrentMenu(value);
}

void MainMenu::OnEvent()
{
	std::string command = Core::GetGuiController()->GetCommand();
	if(command == "btnEditGround")
	{
		Core::GetGuiController()->ShowControl("btnGroundHeightSimple",SLIDE_RIGHT);
		Core::GetGuiController()->ShowControl("btnGroundHeightSmooth",SLIDE_RIGHT);
		Core::GetGuiController()->ShowControl("btnGroundTexture",SLIDE_RIGHT);
		
		Core::GetGuiController()->HideControl("btnEditGround");
		Core::GetGuiController()->HideControl("btnEditGrass");
		Core::GetGuiController()->HideControl("btnSave");
		Core::GetGuiController()->HideControl("btnExit");
	}
	else if(command == "btnPrev")
	{
		Game::GetSceneInstance()->GetHeightmapInstance()->UpdateData(UPDATE_RECREATE);
		Game::GetSceneInstance()->GetWaterInstance()->UpdateData(UPDATE_RECREATE);
	}
	else if(command == "btnGroundHeightSimple")
	{
		Core::GetGuiController()->ShowControl("btnGroundInc",SLIDE_TOP);
		Core::GetGuiController()->ShowControl("btnGroundDec",SLIDE_TOP);

		Core::GetGuiController()->HideControl("btnGroundHeightSimple");
		Core::GetGuiController()->HideControl("btnGroundHeightSmooth");
		Core::GetGuiController()->HideControl("btnGroundTexture");

		Editor::_editHeightmapType = EDIT_HEIGHTMAP_SIMPLE;
	}
	else if(command == "btnGroundHeightSmooth")
	{
		Core::GetGuiController()->ShowControl("btnGroundInc",SLIDE_TOP);
		Core::GetGuiController()->ShowControl("btnGroundDec",SLIDE_TOP);

		Core::GetGuiController()->HideControl("btnGroundHeightSimple");
		Core::GetGuiController()->HideControl("btnGroundHeightSmooth");
		Core::GetGuiController()->HideControl("btnGroundTexture");

		Editor::_editHeightmapType = EDIT_HEIGHTMAP_SMOOTH;
	}
	else if(command == "btnGroundInc")
	{
		Editor::_editType = EDIT_HEIGHTMAP;
		Editor::_editDeltaHeight = 5.0f;
	}
	else if(command == "btnGroundDec")
	{
		Editor::_editType = EDIT_HEIGHTMAP;
		Editor::_editDeltaHeight = -5.0f;
	}
	else if(command == "btnBackMain")
	{
		Core::GetGuiController()->HideAllControl();
		Core::GetGuiController()->ShowControl("btnBackMain",SLIDE_RIGHT);
		Core::GetGuiController()->ShowControl("btnEditGround",SLIDE_LEFT);
		Core::GetGuiController()->ShowControl("btnEditGrass",SLIDE_LEFT);
		Core::GetGuiController()->ShowControl("btnSave",SLIDE_LEFT);
		Core::GetGuiController()->ShowControl("btnExit",SLIDE_LEFT);
		Editor::_editType = EDIT_NONE;
	}
}