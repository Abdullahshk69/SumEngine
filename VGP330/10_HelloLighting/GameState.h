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
	std::vector<SumEngine::Graphics::RenderObject> mPlanets;
	SumEngine::Graphics::StandardEffect mStandardEffect;
};
