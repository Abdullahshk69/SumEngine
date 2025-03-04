#pragma once

#include <SumEngine/Inc/SumEngine.h>


class GameState : public SumEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;
	void Update(float deltaTime);

protected:
	void UpdateCamera(float deltaTime);

	SumEngine::Graphics::Camera mCamera;
	SumEngine::Graphics::DirectionalLight mDirectionalLight;
	SumEngine::Graphics::StandardEffect mStandardEffect;

	SumEngine::Graphics::RenderObject mGround;
	SumEngine::Physics::CollisionShape mGroundShape;
	SumEngine::Physics::RigidBody mGroundRB;

	struct BodyPart
	{
		SumEngine::Graphics::RenderObject segment;
		float range = 0.0f;
	};
	std::vector<BodyPart> mBodyParts;
	SumEngine::Physics::RigidBody mBodyAnchorRB;
	SumEngine::Physics::CollisionShape mBodyShape;
};
