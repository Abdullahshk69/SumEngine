#include "PistolComponent.h"

using namespace SumEngine;
using namespace SumEngine::Input;

void PistolComponent::Update(float deltaTime)
{
    BaseGunComponent::Update(deltaTime);

    auto input = InputSystem::Get();

    if (input->IsMousePressed(MouseButton::LBUTTON))
    {
        Shoot();
    }
}

void PistolComponent::PlayShootingSoundEffect()
{
    mSoundBankComponent->Play("Pistol");
}

void PistolComponent::Deserialize(const rapidjson::Value& value)
{
    if (!SaveUtil::ReadInt("Ammo", mAmmo, value))
    {
        mAmmo = 5;
    }

    mCurrentAmmo = mAmmo;

    if (!SaveUtil::ReadFloat("FireRate", mFireRate, value))
    {
        mFireRate = 0.5f;
    }

    if (!SaveUtil::ReadFloat("Force", mForce, value))
    {
        mForce = 2.0f;
    }

    if (!SaveUtil::ReadFloat("ReloadSpeed", mReloadSpeed, value))
    {
        mReloadSpeed = 2.0f;
    }
}
