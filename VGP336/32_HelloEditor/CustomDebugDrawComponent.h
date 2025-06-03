#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent : public SumEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw() const;

private:
	const SumEngine::TransformComponent* mTransformComponent = nullptr;
	SumEngine::Math::Vector3 mPosition = SumEngine::Math::Vector3::Zero;
	SumEngine::Color mColor = SumEngine::Colors::White;

	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;
};