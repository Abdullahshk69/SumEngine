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
	void OnMoveEvent();
	void OnSpacePressedEvent(const SumEngine::Event& e) const;
	void OnMKeyPressedEvent(const SumEngine::Event& e) const;
	void SetLookAt(const SumEngine::Event& e, SumEngine::Math::Vector3 direction) const;
	void PlayerLaserGunSoundEvent();
	void PlayNextAnimation();
	void PlaySound(int index, float volume = 1.0f);
	void PlayVoice(int index, float volume = 1.0f);
	void StopVoice(int index);

	SumEngine::Graphics::Camera mCamera;
	SumEngine::Graphics::RenderObject mGround;
	SumEngine::Graphics::RenderObject mCube;
	SumEngine::Graphics::DirectionalLight mDirectionalLight;
	SumEngine::Graphics::StandardEffect mStandardEffect;

	std::vector<SumEngine::Audio::SoundId> mSoundIds;
	std::vector<SumEngine::Audio::SoundId> mVoiceIds;

	// Characters
	SumEngine::Graphics::RenderGroup mCharacter;
	SumEngine::Graphics::Animator mCharacterAnimator;

	SumEngine::Graphics::RenderGroup mCharacter2;
	SumEngine::Graphics::Animator mCharacterAnimator2;
	
	// Main animation
	SumEngine::Graphics::Animation mAnimation;
	
	// Camera Animations
	SumEngine::Graphics::Animation mCameraAnimation;
	SumEngine::Graphics::Animation mCameraLookAtAnimation;

	// Particles
	SumEngine::Graphics::ParticleSystemEffect mParticleSystemEffect;
	SumEngine::Physics::ParticleSystem mParticleSystem;
	
	float mAnimationTime = 0.0f;
	int mAnimationIndex1 = -1;
	int mAnimationIndex2 = -1;

	bool mRenderChar1 = true;
	bool mRenderChar2 = true;

	bool mCharFollowAnim1 = false;
	bool mCharFollowAnim2 = false;

	bool mCameraFollow = false;
	bool mCameraSetLookAt = false;

	bool mRenderParticleEffect = false;
};
