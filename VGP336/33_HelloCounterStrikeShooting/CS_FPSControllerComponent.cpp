#include "CS_FPSControllerComponent.h"
#include "BaseGunComponent.h"

#include "../../Engine/SumEngine/Inc/SaveUtil.h"
#include "../../Framework/Physics/Inc/Raycast.h"

using namespace SumEngine;
using namespace SumEngine::Input;
using namespace SumEngine::Graphics;
using namespace SumEngine::Math;
using namespace SumEngine::Physics;

namespace
{
    void SetForward(Vector3& forward, float pitch, float yaw)
    {
        forward.x = cosf(pitch) * sinf(yaw);
        forward.y = -sinf(pitch);
        forward.z = cosf(pitch) * cosf(yaw);
    }

    void SetRight(Vector3& right, float pitch, float yaw)
    {
        right.x = cosf(yaw);
        right.y = 0;
        right.z = -sinf(yaw);
    }

    void SetUp(Vector3& up, float pitch, float yaw)
    {
        up.x = sinf(pitch) * sinf(yaw);
        up.y = cosf(pitch);
        up.z = sinf(pitch) * cosf(yaw);
    }
}

void CS_FPSControllerComponent::Initialize()
{
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
    mRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    mGunComponent = GetOwner().GetComponent<BaseGunComponent>();
    mGunComponent->Pickup(this);

    ASSERT(mTransformComponent != nullptr || mRigidBodyComponent != nullptr, "CS_FPSControllerComponent: neither camera nor rigidbody was found");
}

void CS_FPSControllerComponent::Terminate()
{
    mTransformComponent = nullptr;
    mRigidBodyComponent = nullptr;
    mCameraComponent = nullptr;
}

void CS_FPSControllerComponent::Update(float deltaTime)
{
    auto input = InputSystem::Get();

    // Camera Controls

    //camera.Yaw(input->GetMouseMoveX() * turnSpeed);
    float yaw = input->GetMouseMoveX() * mTurnSpeed;         // How much X turned
    float pitch = input->GetMouseMoveY() * mTurnSpeed;       // How much Y turned

    mYaw += yaw;
    mPitch += pitch;

    // Get the rotate here
    // 
    // radians = Turn speed using mouse
    // 
    // Use YAW to rotate the model as well
    mCameraComponent->GetCamera().Yaw(yaw);
    mCameraComponent->GetCamera().Pitch(pitch);


    // This is only Up and down. Character rotation will not be affected by this
    //camera.Pitch(input->GetMouseMoveY() * turnSpeed);

    // Character Controls
    // WASD based on forward and right

    SetForward(mForward, mPitch, mYaw);
    SetRight(mRight, mPitch, mYaw);
    SetUp(mUp, mPitch, mYaw);

    Vector3 walk = { mForward.x, 0, mForward.z };
    Vector3 strafe = { mRight.x, 0, mRight.z };

    Vector3 moveDirection = Vector3::Zero;

    if (input->IsKeyDown(KeyCode::W))
    {
        moveDirection += walk;
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        moveDirection += -walk;
    }

    if (input->IsKeyDown(KeyCode::A))
    {
        moveDirection += -strafe;
    }
    else if (input->IsKeyDown(KeyCode::D))
    {
        moveDirection += strafe;
    }

    // If there is a move direction
    if (moveDirection.x != 0 ||
        moveDirection.y != 0 ||
        moveDirection.z != 0)
    {
        moveDirection = Math::Normalize(moveDirection);
        moveDirection *= input->IsKeyDown(KeyCode::LSHIFT) ? mWalkSpeed : mMoveSpeed;
        mRigidBodyComponent->SetVelocity(moveDirection);
    }
    mCameraComponent->GetCamera().SetPosition(mTransformComponent->position);
}

void CS_FPSControllerComponent::DebugUI()
{
    if (ImGui::CollapsingHeader("CharacterController"))
    {
        ImGui::DragFloat("TurnSpeed", &mTurnSpeed, 0.01);
        ImGui::DragFloat("WalkSpeed", &mWalkSpeed, 0.01);
        ImGui::DragFloat("MoveSpeed", &mMoveSpeed, 0.01);
    }
}

const Vector3 CS_FPSControllerComponent::GetForwardVector() const
{
    return mForward;
}

const Vector3 CS_FPSControllerComponent::GetPosition() const
{
    return mTransformComponent->position;
}

void CS_FPSControllerComponent::Deserialize(const rapidjson::Value& value)
{
    SaveUtil::ReadFloat("MoveSpeed", mMoveSpeed, value);
    SaveUtil::ReadFloat("TurnSpeed", mTurnSpeed, value);
    SaveUtil::ReadFloat("WalkSpeed", mWalkSpeed, value);
}
