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

	SumEngine::Graphics::RenderGroup mCharacter;
	SumEngine::Graphics::DirectionalLight mDirectionalLight;
	SumEngine::Graphics::StandardEffect mStandardEffect;
	SumEngine::Graphics::StandardEffect mRenderTargetStandardEffect;
	SumEngine::Graphics::RenderTarget mRenderTarget;
};
