#include "CS_FPSControllerComponent.h"
#include "../../Engine/SumEngine/Inc/RigidBodyComponent.h"
#include "../../Engine/SumEngine/Inc/SaveUtil.h"

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

    if (input->IsKeyDown(KeyCode::W))
    {
        mRigidBodyComponent->SetVelocity(walk * mMoveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mRigidBodyComponent->SetVelocity(walk * -mMoveSpeed);
    }

    if (input->IsKeyDown(KeyCode::A))
    {
        mRigidBodyComponent->SetVelocity(strafe * -mMoveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::D))
    {
        mRigidBodyComponent->SetVelocity(strafe * mMoveSpeed);
    }

    mCameraComponent->GetCamera().SetPosition(mTransformComponent->position);
}

void CS_FPSControllerComponent::DebugUI()
{
    SimpleDraw::AddLine(Vector3::Zero, mForward, Colors::Red);
    SimpleDraw::AddLine(Vector3::Zero, mRight, Colors::Green);
    SimpleDraw::AddLine(Vector3::Zero, mUp, Colors::Blue);
}

void CS_FPSControllerComponent::Deserialize(const rapidjson::Value& value)
{
    SaveUtil::ReadFloat("MoveSpeed", mMoveSpeed, value);
    SaveUtil::ReadFloat("TurnSpeed", mTurnSpeed, value);
}

void CS_FPSControllerComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value, const rapidjson::Value& original)
{

}