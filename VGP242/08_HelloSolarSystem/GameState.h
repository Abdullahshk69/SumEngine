#pragma once

#include <SumEngine/Inc/SumEngine.h>

enum class SolarSystem
{
	Sun,		// 109
	Mercury,	// 0.3
	Venus,		// 0.8
	Earth,		// 1
	Mars,		// 0.5
	Jupiter,	// 11
	Saturn,		// 10
	Uranus,		// 4
	Neptune,	// 4
	Pluto,		// 0.2
	Galaxy,
	End
};


struct TexturedObject
{
	SumEngine::Math::Matrix4 transform;
	// localRotation (day/night)
	// orbitRotation(year)
	// distanceFromSun
	// transform = Matrix4::RotationY(localRotation) * Matrix4::Translation(Vector3::zAxis * distanceFromSun) * Matrix4::Rotation(orbitRotation)

	// For moon: same transform as above but multiply Earth's position in world space at the end
	// position = { transform._41, transform._42, transform._43 }

	SumEngine::Graphics::MeshBuffer mMeshBuffer;
	SumEngine::Graphics::Texture mDiffuseTexture;

	float orbitSpeed;
	float rotationSpeed;
	float distanceFromSun;

	void UpdatePosition()
	{

	}

	void Render()
	{

	}
};

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

	TexturedObject mObjects[(int)SolarSystem::End];
	SumEngine::Graphics::Camera mCamera;
	SumEngine::Graphics::Camera mRenderTargetCamera;
	SumEngine::Graphics::ConstantBuffer mConstantBuffer;
	SumEngine::Graphics::MeshBuffer mMeshBuffer;
	SumEngine::Graphics::VertexShader mVertexShader;
	SumEngine::Graphics::PixelShader mPixelShader;
	SumEngine::Graphics::Texture mDiffuseTexture;
	SumEngine::Graphics::Sampler mSampler;
	SumEngine::Graphics::RenderTarget mRenderTarget;

	SolarSystem mCurrentTarget = SolarSystem::Sun;
};
