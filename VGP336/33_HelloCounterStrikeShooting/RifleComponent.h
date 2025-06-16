#pragma once

#include "BaseGunComponent.h"

class RifleComponent : public BaseGunComponent
{
public:
    void Update(float deltaTime) override;
    void Deserialize(const rapidjson::Value& value) override;

    void PlayShootingSoundEffect() override;
};