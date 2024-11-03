#include "GameState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	float x = 0.0f;
	Mesh mesh = MeshBuilder::CreateSphere(300, 300, 1.0f);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	std::filesystem::path shaderFile2 = L"../../Assets/Shaders/CelShading.fx";
	mRenderTargetStandardEffect.Initialize(shaderFile2);
	mRenderTargetStandardEffect.SetCamera(mCamera);
	mRenderTargetStandardEffect.SetDirectionalLight(mDirectionalLight);

	mCharacter1.Initialize(L"../../Assets/Models/Ortiz/Ch43_nonPBR.model");
	mCharacter2.Initialize(L"../../Assets/Models/Vanguard/VanguardByT.Choonyung.model");

	const uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U8);
}

void GameState::Terminate()
{
	mRenderTargetStandardEffect.Terminate();
	mRenderTarget.Terminate();
	mCharacter2.Terminate();
	mCharacter1.Terminate();
	mStandardEffect.Terminate();
}


void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
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
	mCamera.SetAspectRatio(1.0f);
	mRenderTarget.BeginRender();
		mRenderTargetStandardEffect.Begin();
			if (checkBox)
			{
				mRenderTargetStandardEffect.Render(mCharacter1);
			}
			else
			{
				mRenderTargetStandardEffect.Render(mCharacter2);
			}
		mRenderTargetStandardEffect.End();
	mRenderTarget.EndRender();

	mCamera.SetAspectRatio(0.0f);

	mStandardEffect.Begin();
		mStandardEffect.Render(mCharacter1);
	mStandardEffect.End();

	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
			{
				mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
			}

			ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
			ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
			ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
		}

		ImGui::Separator();
		ImGui::Text("RenderTarget");
		ImGui::Image(
			mRenderTarget.GetRawData(),
			{ 128,128 },
			{ 0,0 },
			{ 1,1 },
			{ 1, 1, 1,1 },
			{ 1, 1, 1,1 }
		);

		ImGui::Checkbox("CheckBox", &checkBox);
	mStandardEffect.DebugUI();
	ImGui::End();
}

