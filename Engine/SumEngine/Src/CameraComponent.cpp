#include "Precompiled.h"
#include "CameraComponent.h"

using namespace SumEngine;
using namespace SumEngine::Graphics;
using namespace SumEngine::Math;

void CameraComponent::Initialize()
{
}

void CameraComponent::Terminate()
{
}

void CameraComponent::DebugUI()
{
	Vector3 pos = mCamera.GetPosition();
	if (ImGui::DragFloat3("Position##Camera", &pos.x, 0.1f))
	{
		mCamera.SetPosition(pos);
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
