#pragma once

#include <SumEngine/Inc/SumEngine.h>

class EditTemplateState : public SumEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Render() override;
	void DebugUI() override;
	void Update(float deltaTime);

protected:
	SumEngine::GameWorld mGameWorld;
};
