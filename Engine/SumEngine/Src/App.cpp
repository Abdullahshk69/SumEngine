#include "Precompiled.h"
#include "App.h"

using namespace SumEngine;
using namespace SumEngine::Core;

void App::Run()
{
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		L"HelloWindow",
		600,
		400
	);

	(void)TimeUtil::GetTime();	// Initialize the first time stamp
	
	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();

		if (!myWindow.IsActive())
		{
			Quit();
		}
	}

	myWindow.Terminate();
}

void App::Quit()
{
	mRunning = false;
}
