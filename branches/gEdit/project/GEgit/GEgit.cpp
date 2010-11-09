#include "MainForm.h"
#include "../../Source/Core/CGlobal.h"
#include "../../Source/Game.h"

using namespace GEgit;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	MainForm ^_mainForm = gcnew MainForm();
	Core::CGlobal::SetHWND((HWND)_mainForm->Handle.ToPointer());
	Core::CGlobal::AddHWNDToList((HWND)_mainForm->splitContainer1->Panel1->Handle.ToPointer());
	Core::CGlobal::AddHWNDToList((HWND)_mainForm->splitContainer1->Panel2->Handle.ToPointer());

	Game* gameInstance = new Game();
	gameInstance->Create();

	_mainForm->Show();
	while(_mainForm->Created)
	{
		Application::DoEvents();
		gameInstance->Update(0);
		gameInstance->Render();
	}
	return 0;
}
