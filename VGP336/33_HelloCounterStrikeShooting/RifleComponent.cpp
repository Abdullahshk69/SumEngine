#include "RifleComponent.h"

using namespace SumEngine;
using namespace SumEngine::Input;

void RifleComponent::Update(float deltaTime)
{
    BaseGunComponent::Update(deltaTime);

    auto input = InputSystem::Get();

    if (input->IsMouseDown(MouseButton::LBUTTON))
    {
        Shoot();
    }
}

void RifleComponent::Deserialize(const rapidjson::Value& value)
{
    if (!SaveUtil::ReadInt("Ammo", mAmmo, value))
    {
        mAmmo = 30;
    }

    mCurrentAmmo = mAmmo;

    if (!SaveUtil::ReadFloat("FireRate", mFireRate, value))
    {
        mFireRate = 0.5f;
    }

    if (!SaveUtil::ReadFloat("Force", mForce, value))
    {
        mForce = 50.0f;
    }

    if (!SaveUtil::ReadFloat("ReloadSpeed", mReloadSpeed, value))
    {
        mReloadSpeed = 3.0f;
    }
}

void RifleComponent::PlayShootingSoundEffect()
{
    mSoundBankComponent->Play("Rifle");
}
