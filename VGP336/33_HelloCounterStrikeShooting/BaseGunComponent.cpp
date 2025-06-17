#include "BaseGunComponent.h"
#include "CS_FPSControllerComponent.h"

using namespace SumEngine;
using namespace SumEngine::Input;
using namespace SumEngine::Math;
using namespace SumEngine::Physics;

void BaseGunComponent::Initialize()
{
    mSoundBankComponent = GetOwner().GetComponent<SoundBankComponent>();
}

void BaseGunComponent::Terminate()
{
    mAgent = nullptr;
    mSoundBankComponent = nullptr;
}

void BaseGunComponent::Update(float deltaTime)
{
    if (mCurrentFireBuffer > 0.0f)
    {
        mCurrentFireBuffer -= deltaTime;

        if (mCurrentFireBuffer <= 0.0f && mCurrentAmmo == 0)
        {
            Reload();
        }
    }

    if (mReloadTimerBuffer > 0.0f)
    {
        mReloadTimerBuffer -= deltaTime;

        if (mReloadTimerBuffer <= 0.0f)
        {
            ReloadFinish();
        }
    }
}

void BaseGunComponent::DebugUI()
{
    if (ImGui::CollapsingHeader("Gun"))
    {
        ImGui::DragInt("Ammo", &mAmmo);
        ImGui::DragFloat("FireRate", &mFireRate, 0.01f);
        ImGui::DragFloat("ReloadSpeed", &mReloadSpeed, 0.01f);
    }
}

void BaseGunComponent::Shoot()
{
    if (mCurrentFireBuffer > 0.0f || mIsReloading || !mIsEquipped)
    {
        return;
    }

    Vector3 aim = mAgent->GetForwardVector();
    Raycast raycast;
    bool hit = raycast.Cast(mAgent->GetPosition(), mAgent->GetForwardVector(), 100.0f);

    if (hit)
    {
        RaycastHit* raycastHit = raycast.GetRaycastResult();
        GameObject* hitObject = raycastHit->gameObject;

        RigidBodyComponent* rb = hitObject->GetComponent<RigidBodyComponent>();
        if (rb)
        {
            rb->AddForce(mAgent->GetForwardVector() * mForce);
        }
    }
    PlayShootingSoundEffect();
    mCurrentFireBuffer = mFireRate;
    mCurrentAmmo--;
}

void BaseGunComponent::Reload()
{
    if (!mIsReloading && mCurrentAmmo < mAmmo)
    {
        ReloadStart();
    }
}

void BaseGunComponent::ReloadStart()
{
    mReloadTimerBuffer = mReloadSpeed;
    mIsReloading = true;
    PlayReloadingSoundEffect();
}

void BaseGunComponent::ReloadFinish()
{
    mCurrentAmmo = mAmmo;
    mIsReloading = false;
}

void BaseGunComponent::Pickup(CS_FPSControllerComponent* agent)
{
    mAgent = agent;
    mIsEquipped = true;
}

void BaseGunComponent::Drop()
{
    mIsEquipped = false;
}

void BaseGunComponent::Switch()
{
    mIsEquipped = false;
}
