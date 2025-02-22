#include "GameState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;
using namespace SumEngine::Physics;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mParticleSystemEffect.Initialize();

	ParticleSystemInfo info;
	mParticleSystem.Initialize(info);
}

void GameState::Terminate()
{
	mParticleSystem.Terminate();
	mParticleSystemEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	mParticleSystem.Update(deltaTime);
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
	const float turnSpeed = 0.1f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

bool checkBox = true;

void GameState::Render()
{
	mParticleSystemEffect.Begin();
		mParticleSystem.Render(mParticleSystemEffect);
	mParticleSystemEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mParticleSystem.DebugUI();
	mParticleSystemEffect.DebugUI();
	PhysicsWorld::Get()->DebugUI();
	ImGui::End();
	SimpleDraw::Render(mCamera);
}
