#include "GameState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;
using namespace SumEngine::Audio;

void GameState::Initialize()
{
	// Make Baseball swing hitting a ball
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	Mesh mesh = MeshBuilder::CreateSphere(300, 300, 1.0f);

	std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	mCharacter.Initialize(L"../../Assets/Models/Ortiz/Ch43_nonPBR.model", &mCharacterAnimator);

	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/JumpingDown_1.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Standing_1.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Falling_1.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/FallingFlatImpact.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/BicycleCrunch.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/StandingReactDeathForward.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HeadHit_1.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HeadHit_2.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HeadHit_3.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/PunchingBag.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Swinging.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HurricaneKick.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/BodyBlock.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/CenterBlock_1.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/CenterBlock_2.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Chapa-Giratoria.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/DropKick.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/FlyingKneePunchCombo.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/JumpAttack.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Martelo2.model");
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/StandingUp.model");
	mCharacterAnimator.Initialize(mCharacter.modelId);

	AnimationKeyEvent ake;
	ake.SetIndex(2);

	mAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f, 0.5f, 0.0f }, 0.0f)
		.AddParameterEventKey(std::bind(&GameState::OnMKeyPressedEvent, this, ake), 0.5f)
		.AddParameterEventKey(std::bind(&GameState::OnMKeyPressedEvent, this, AnimationKeyEvent(10)), 1.0f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 1.0f)
		.AddPositionKey({ 1.0f, 0.5f, 0.0f }, 0.4f)
		.AddEventKey(std::bind(&GameState::PlayNextAnimation, this), 2.0f)
		.Build();

	mAnimationTime = 0.0f;

	EventManager* em = EventManager::Get();
	mSpacePressedEventId = em->AddListener(EventType::SpacePressed, std::bind(&GameState::OnSpacePressedEvent, this, std::placeholders::_1));
	mMKeyPressedEventId = em->AddListener(EventType::AnimationKey, std::bind(&GameState::OnMKeyPressedEvent, this, std::placeholders::_1));

	mGunEventId = SoundEffectManager::Get()->Load("photongun1.wav");
	mLaserGunEventId = SoundEffectManager::Get()->Load("megamanx_blast.wav");
	mExplosionEventId = SoundEffectManager::Get()->Load("explosion.wav");
	mHonseEventId = SoundEffectManager::Get()->Load("honse.wav");
}

void GameState::Terminate()
{
	mCharacter.Terminate();
	EventManager::Get()->RemoveListener(EventType::SpacePressed, mSpacePressedEventId);
	EventManager::Get()->RemoveListener(EventType::MKeyPressed, mHonseEventId);
	mGround.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	if (mAnimation.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mAnimationTime += deltaTime;
		mAnimation.PlayEvent(prevTime, mAnimationTime);
		Event event;
		mAnimation.PlayParameterEvent(prevTime, mAnimationTime, event);
		//while (mAnimationTime > mAnimation.GetDuration())
		//{
		//	mAnimationTime -= mAnimation.GetDuration();	// Simple loop
		//}
	}

	mCharacterAnimator.Update(deltaTime);

	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		SpacePressedEvent spe;
		EventManager::Broadcast(spe);
	}

	if (InputSystem::Get()->IsKeyPressed(KeyCode::M))
	{
		AnimationKeyEvent ake;
		ake.SetIndex(2);
		EventManager::Broadcast(ake);
	}
}

void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
	const float turnSpeed = 0.1f * deltaTime;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

void GameState::PlayNextAnimation()
{
	mAnimationIndex++;
	if (mAnimationIndex >= mCharacterAnimator.GetAnimationCount())
	{
		mAnimationIndex = 0;
	}
	mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
}

void GameState::OnSpacePressedEvent(const SumEngine::Event& e) const
{
	LOG("HEY THE SPACE WAS PRESSED");
	SoundEffectManager::Get()->Play(mGunEventId);
}

void GameState::OnMKeyPressedEvent(const SumEngine::Event& e) const
{
	const AnimationKeyEvent& mkpe = static_cast<const AnimationKeyEvent&>(e);
	LOG("%d", mkpe.GetIndex());
	LOG("M Key Pressed");
	SoundEffectManager::Get()->Play(mHonseEventId);
}

void GameState::SetLookAt(const SumEngine::Event& e, SumEngine::Math::Vector3 direction) const
{
	LOG("Set Look At called");
}

void GameState::PlayerLaserGunSoundEvent()
{
	SoundEffectManager::Get()->Play(mLaserGunEventId);
}

bool checkBox = true;

void GameState::Render()
{
	//mCamera.SetPosition(mAnimation.GetTransform(mAnimationTime).position);
	//mCamera.SetLookAt(mCharacter.transform.position);

	mStandardEffect.Begin();
	mStandardEffect.Render(mGround);
	mStandardEffect.Render(mCharacter);
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}

		int maxAnimations = mCharacterAnimator.GetAnimationCount();
		if (ImGui::DragInt("AnimIndex", &mAnimationIndex, 1, -1, maxAnimations - 1))
		{
			mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	ImGui::End();
}
