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
	
	// ball info
	SumEngine::Graphics::RenderObject mBall;
	SumEngine::Physics::CollisionShape mBallShape;
	SumEngine::Physics::RigidBody mBallRB;

	// ground info
	SumEngine::Graphics::RenderObject mGround;
	SumEngine::Physics::CollisionShape mGroundShape;
	SumEngine::Physics::RigidBody mGroundRB;

	// cloth info
	SumEngine::Graphics::RenderObject mCloth;
	SumEngine::Graphics::Mesh mClothMesh;
	SumEngine::Physics::SoftBody mClothSoftBody;
};
