#include <SumEngine/Inc/SumEngine.h>

#include "GameState.h"
#include "EditTemplateState.h"

using namespace SumEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appname = L"Hello Game Game World";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.AddState<EditTemplateState>("EditTemplateState");
	myApp.Run(config);
	return(0);
}