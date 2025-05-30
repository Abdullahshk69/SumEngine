#include "Precompiled.h"
#include "CameraComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "CameraService.h"

using namespace SumEngine;
using namespace SumEngine::Graphics;
using namespace SumEngine::Math;

void CameraComponent::Initialize()
{
	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	if (cameraService != nullptr)
	{
		cameraService->Register(this);
	}
}

void CameraComponent::Terminate()
{
	CameraService* cameraService = GetOwner().GetWorld().GetService<CameraService>();
	if (cameraService != nullptr)
	{
		cameraService->Unregister(this);
	}
}

void CameraComponent::DebugUI()
{
	Vector3 pos = mCamera.GetPosition();
	if (ImGui::DragFloat3("Position##Camera", &pos.x, 0.1f))
	{
		mCamera.SetPosition(pos);
	}
}

void CameraComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("Position"))
	{
		const auto& pos = value["Position"].GetArray();
		const float x = pos[0].GetFloat();
		const float y = pos[1].GetFloat();
		const float z = pos[2].GetFloat();
		mCamera.SetPosition({ x, y, z });
	}
	if (value.HasMember("LookAt"))
	{
		const auto& pos = value["LookAt"].GetArray();
		const float x = pos[0].GetFloat();
		const float y = pos[1].GetFloat();
		const float z = pos[2].GetFloat();
		mCamera.SetLookAt({ x, y, z });
	}
}

Camera& CameraComponent::GetCamera()
{
	return mCamera;
}

const Camera& CameraComponent::GetCamera() const
{
	return mCamera;
}
