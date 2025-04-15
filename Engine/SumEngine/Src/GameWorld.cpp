#include "Precompiled.h"
#include "GameWorld.h"

using namespace SumEngine;

void GameWorld::Initialize()
{
	ASSERT(!mInitialized, "GameWorld: is already initialized");
	for (auto& service : mServices)
	{
		service->Initialize();
	}

	mInitialized = true;
}

void GameWorld::Terminate()
{
	for (auto& gameObject : mGameObjects)
	{
		gameObject->Terminate();
		gameObject.reset();
	}
	mGameObjects.clear();

	for (auto& service : mServices)
	{
		service->Terminate();
		service.reset();
	}
	mServices.clear();
}

void GameWorld::Update(float deltaTime)
{
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}

	for (auto& service : mServices)
	{
		service->Update(deltaTime);
	}
}

void GameWorld::Render()
{
	for (auto& service : mServices)
	{
		service->Render();
	}
}

void GameWorld::DebugUI()
{
	for (auto& go : mGameObjects)
	{
		go->DebugUI();
	}

	for (auto& service : mServices)
	{
		service->DebugUI();
	}
}

GameObject* GameWorld::CreateGameObject(std::string name)
{
	ASSERT(mInitialized, "GameWorld: is not initialized");
	auto& newGO = mGameObjects.emplace_back(std::make_unique<GameObject>());
	newGO->SetName(name);
	return newGO.get();
}
