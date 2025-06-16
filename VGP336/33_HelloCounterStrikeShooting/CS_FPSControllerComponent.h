#pragma once

#include "CustomTypeIds.h"

class BaseGunComponent;

class CS_FPSControllerComponent : public SumEngine::Component	// Copying camera component
{
public:
    SET_TYPE_ID(CustomComponentId::CS_FPSCamera);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void DebugUI() override;

	const SumEngine::Math::Vector3 GetForwardVector() const;
	const SumEngine::Math::Vector3 GetPosition() const;

	void Deserialize(const rapidjson::Value& value) override;

private:
	SumEngine::TransformComponent* mTransformComponent = nullptr;		// To rotate model
	SumEngine::RigidBodyComponent* mRigidBodyComponent = nullptr;
	SumEngine::CameraComponent* mCameraComponent = nullptr;				// To rotate camera
	BaseGunComponent* mGunComponent = nullptr;

	float mMoveSpeed = 2.0f;
	float mWalkSpeed = 1.0f;

	float mJumpForce = 10.0f;
	float mTurnSpeed = 1.0f;

	float mPitch = 0.0f;
	float mYaw = 0.0f;

	bool mIsIdle = true;
	bool mIsWalking = false;
	bool mIsRunning = false;
	bool mIsJumping = false;

	SumEngine::Math::Vector3 mForward = SumEngine::Math::Vector3::Zero;
	SumEngine::Math::Vector3 mRight = SumEngine::Math::Vector3::Zero;
	SumEngine::Math::Vector3 mUp = SumEngine::Math::Vector3::Zero;
};