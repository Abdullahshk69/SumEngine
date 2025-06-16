#pragma once

#include "CustomTypeIds.h"

class CS_FPSControllerComponent;
class BaseGunComponent : public SumEngine::Component
{
public:
    SET_TYPE_ID(CustomComponentId::BaseGun);

    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;

    void DebugUI() override;

    virtual void Shoot();
    virtual void ReloadStart();
    virtual void ReloadFinish();
    virtual void Pickup(CS_FPSControllerComponent* agent);
    virtual void Drop();
    virtual void Switch();
    virtual void PlayShootingSoundEffect() {}
    virtual void PlayReloadingSoundEffect() { mSoundBankComponent->Play("Reloading"); }

protected:
    int mAmmo = 5;
    int mCurrentAmmo = 5;
    float mFireRate = 1.0f;
    float mCurrentFireBuffer = 0.0f;
    float mForce = 1.0f;
    float mReloadSpeed = 2.0f;
    float mReloadTimerBuffer = 0.0f;
    bool mIsReloading = false;
    bool mIsEquipped = false;
    CS_FPSControllerComponent* mAgent = nullptr;
    SumEngine::SoundBankComponent* mSoundBankComponent = nullptr;
};