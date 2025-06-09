#include "GameState.h"
#include "CS_FPSControllerComponent.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;
using namespace SumEngine::Audio;

//Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
//{
//	if (serviceName == "CS_CharacterMovementComponent")
//	{
//		return gameWorld.AddService<CS_CharacterMovementComponent>();
//	}
//	return nullptr;
//}

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CS_FPSControllerComponent")
	{
		return gameObject.AddComponent<CS_FPSControllerComponent>();
	}
	return nullptr;
}

Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CS_FPSControllerComponent")
	{
		return gameObject.GetComponent<CS_FPSControllerComponent>();
	}
	return nullptr;
}


void GameState::Initialize()
{
	//GameWorld::SetCustomService(CustomServiceMake);
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);

	mGameWorld.LoadLevel(L"../../Assets/Templates/Levels/final_level.json");
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mGameWorld.DebugUI();
	ImGui::End();
}
