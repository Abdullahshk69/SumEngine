#pragma once

#include "CustomTypeIds.h"

// FPS Controller
class CS_CharacterMovementComponent : public SumEngine::Component
{
    SET_TYPE_ID(CustomComponentId::CS_CharacterMovement);

    void Initialize() override;
    void Terminate() override;
    void Deserialize(const rapidjson::Value& value) override;

    void Update(float deltaTime) override;

private:
    const SumEngine::RigidBodyComponent* mRigidBodyComponent = nullptr;
    const SumEngine::CameraComponent* mCamera = nullptr;
    float mMoveSpeed = 2.0f;
    float mWalkSpeed = 1.0f;
};