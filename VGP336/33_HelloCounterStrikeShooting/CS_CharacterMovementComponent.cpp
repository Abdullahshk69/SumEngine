#include "CS_CharacterMovementComponent.h"

using namespace SumEngine;
using namespace SumEngine::Input;

void CS_CharacterMovementComponent::Initialize()
{

}

void CS_CharacterMovementComponent::Terminate()
{

}

void CS_CharacterMovementComponent::Deserialize(const rapidjson::Value& value)
{

}

void CS_CharacterMovementComponent::Update(float deltaTime)
{
    // Get inputs and apply then using Camera look direction (NO Z AXIS MOVEMENT)

    // WASD
    SumEngine::Math::Vector3 moveDirection;

    auto input = InputSystem::Get();
    const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? mWalkSpeed : mMoveSpeed) * deltaTime;

    // Get the Forward vector for W and S and Get the Right vector for Left and Right

    // JUMP

    // CTRL

}
