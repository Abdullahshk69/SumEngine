#include "Precompiled.h"
#include "FPSCameraComponent.h"

#include "CameraComponent.h"
#include "GameObject.h"
#include "SaveUtil.h"

using namespace SumEngine;
using namespace Graphics;
using namespace Input;
using namespace Math;

void FPSCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: camera was not found");
}

void FPSCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
}

void FPSCameraComponent::Update(float deltaTime)
{
	Camera& camera = mCameraComponent->GetCamera();
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? mShiftSpeed : mMoveSpeed) * deltaTime;
	const float turnSpeed = mTurnSpeed * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		camera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		camera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		camera.Yaw(input->GetMouseMoveX() * turnSpeed);
		camera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

void FPSCameraComponent::Deserialize(const rapidjson::Value& value)
{
	SaveUtil::ReadFloat("MoveSpeed", mMoveSpeed, value);
	SaveUtil::ReadFloat("ShiftSpeed", mShiftSpeed, value);
	SaveUtil::ReadFloat("TurnSpeed", mTurnSpeed, value);
}

void FPSCameraComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value, const rapidjson::Value& original)
{
	rapidjson::Value componentValue(rapidjson::kObjectType);
	SaveUtil::WriteFloat("MoveSpeed", mMoveSpeed, doc, componentValue);
	SaveUtil::WriteFloat("ShiftSpeed", mShiftSpeed, doc, componentValue);
	SaveUtil::WriteFloat("TurnSpeed", mTurnSpeed, doc, componentValue);
	value.AddMember("FPSCameraComponent", componentValue, doc.GetAllocator());
}
