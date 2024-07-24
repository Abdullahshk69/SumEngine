#include "Precompiled.h"
#include "App.h"

using namespace SumEngine;

void App::Run()
{
	mRunning = true;
	while (mRunning)
	{
		// update
	}
}

void App::Quit()
{
	mRunning = false;
}
