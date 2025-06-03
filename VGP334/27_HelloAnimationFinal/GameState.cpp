#include "GameState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;
using namespace SumEngine::Audio;
using namespace SumEngine::Physics;

// Here are the steps required to animate my gorgeous materpiece
//
// 1- Set the default positions for the characters
//

void GameState::Initialize()
{
	mCamera.SetPosition({ -8.0f, 3.5f, -0.6f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderFile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	Mesh ground = MeshBuilder::CreateGroundPlane(20, 20, 2.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	MeshPX cube = MeshBuilder::CreateCubePX(1.0f);
	mCube.meshBuffer.Initialize(cube);
	mCube.diffuseMapId = TextureCache::Get()->LoadTexture("Images/crate.bmp");

	mCube.transform.position.z += 3.0f;
	mCube.transform.position.y += 0.25f;


	mCharacter.Initialize(L"../../Assets/Models/Ortiz/Ch43_nonPBR.model", &mCharacterAnimator);
	mCharacter.transform.position.z += 3.0f;
	mCharacter.transform.position.y += 0.75f;

	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/JumpingDown_1.model");	// 0
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Standing_1.model");	// 1
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Falling_1.model");	// 2
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/FallingFlatImpact.model");	// 3
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/BicycleCrunch.model");	// 4
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/StandingReactDeathForward.model");	// 5
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HeadHit_1.model");	// 6
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HeadHit_2.model");	// 7
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HeadHit_3.model");	// 8
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/PunchingBag.model");	// 9
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Swinging.model");	// 10
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HurricaneKick.model");	// 11
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/BodyBlock.model");	// 12
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/CenterBlock_1.model");	// 13
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/CenterBlock_2.model");	// 14
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Chapa-Giratoria.model");	// 15
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/DropKick.model");	// 16
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/FlyingKneePunchCombo.model");	// 17
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/JumpAttack.model");	// 18
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/Martelo2.model");	// 19
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/FightIdle.model");	// 20
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/StandingUp.model");	// 21
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/MutantPunch.model");	// 22
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/StandingMeleeAttackKick.model");	// 23
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Ortiz/HipHopDancing.model");	// 24
	mCharacterAnimator.Initialize(mCharacter.modelId);

	mCharacter2.Initialize(L"../../Assets/Models/Vanguard/VanguardByT.Choonyung.model", &mCharacterAnimator2);
	mCharacter2.transform.rotation = Quaternion::CreateFromAxisAngle(Vector3::YAxis, 180.0f * Math::Constants::DegToRad);
	mCharacter2.transform.position.z -= 5.0f;

	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Reaction.model");	// 1
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Defeated.model");	// 2
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/DodgingRight.model");	// 3
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Dying.model");	// 4
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/HipHopDancing.model");	// 5
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/StrokeShakingHead.model");	// 6
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/BrutalAssassination.model");	// 7
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/MutantPunch.model");	// 8
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Boxing.model");	// 9
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/FlyingKick.model");	// 10
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/HookPunch.model");	// 11
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/HurricaneKick.model");	// 12
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Martelo2.model");	// 13
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Punching.model");	// 14
	ModelCache::Get()->AddAnimation(mCharacter2.modelId, L"../../Assets/Models/Vanguard/Idle.model");	// 15
	mCharacterAnimator2.Initialize(mCharacter2.modelId);

	// Sound clips
	mSoundIds.push_back(SoundEffectManager::Get()->Load("Mexicanstandoff.wav"));

	// Voice clips
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_1_Introduction.wav"));	// 0
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_2_ChiefJspanwa.wav"));	// 1
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_3_WelcomeChiefJspanwa.wav"));	// 2
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_4a_IntroducingElChupacabra.wav"));	// 3
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_4b_IntroducingElChupacabra.wav"));	// 4
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_5_OnOurRightAUGH.wav"));	// 5
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_6a_LookingToOurRight.wav"));	// 6
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_7_WhatCanMarsianDo.wav"));	// 7
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_8_LetTheFightBegin.wav"));	// 8
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_9_ThatJumpJustShookTheWorld.wav"));	// 9
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_10a_AAAA.wav"));	// 10
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_10b_AAAA_Jspanwa.wav"));			// 11	// 0.1f volume
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_10c_AAAA_Abd.wav"));	// 12
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_10d_AAAA_AbdulHaq.wav"));	// 13
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_11a_ElChupacabraMissing.wav"));	// 14
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_11b_FromTheScreen.wav"));	// 15
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_12_WhatADodge.wav"));	// 16
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_13_ElChupacabraSignatureMove.wav"));	// 17
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_14_WillNeverForgetTheHug.wav"));	// 18
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_15_TheHimIsDown.wav"));	// 19
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_16_IAMTHESTORMTHATISAPPROACHING.wav"));	// 20
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_17a_Lattu.wav"));	// 21
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_17b_Beyblade.wav"));	// 22
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_18_MotivationalSpeech.wav"));	// 23
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_19_HeStand.wav"));	// 24
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_20_ChiefJspanwaLeft.wav"));	// 25
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_21_ReachingClimax.wav"));	// 26
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_22_SpinningToDeath.wav"));	// 27
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_23_BicycleKick.wav"));	// 28
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_24_TimeForElimination.wav"));	// 29
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_25_SentToMars.wav"));	// 30
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_1.wav"));	// 31
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_2.wav"));	// 32
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_3.wav"));	// 33
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_4.wav"));	// 34
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_5.wav"));	// 35
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_6.wav"));	// 36
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_7.wav"));	// 37
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_8.wav"));	// 38
	mVoiceIds.push_back(SoundEffectManager::Get()->Load("Line_Counting_9.wav"));	// 39

	// Main animation of the game
	// Control the character Animations from this
	float voiceTimer = 0.0f;
	mAnimation = AnimationBuilder()
		.AddPositionKey(mCharacter2.transform.position, 0.01f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(20, true); }, 0.01f)
		//.AddEventKey(Test, 3.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(15, true); }, 0.01f)
		.AddEventKey([&]() { PlayVoice(0); }, voiceTimer += 0.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(24, true); }, voiceTimer + 5.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(14, true); }, voiceTimer + 6.0f)
		.AddEventKey([&]() { PlayVoice(1); }, voiceTimer += 7.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(4, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(10, true); }, voiceTimer + 1.0f)

		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(21, true); }, voiceTimer + 5.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(14, true); }, voiceTimer + 6.0f)
		.AddEventKey([&]() { PlayVoice(2); }, voiceTimer += 8.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(13, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(3, true); }, voiceTimer)

		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(10, true); }, voiceTimer + 8.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(7, true); }, voiceTimer + 8.0f)
		.AddEventKey([&]() { PlayVoice(3); }, voiceTimer += 10.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(16, true); }, voiceTimer + 5.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(15, true); }, voiceTimer + 5.0f)

		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(11, true); }, voiceTimer + 13.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(11, true); }, voiceTimer + 13.0f)
		.AddEventKey([&]() { PlayVoice(4); }, voiceTimer += 18.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(22, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(3, true); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(5); }, voiceTimer += 8.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(1, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(8, true); }, voiceTimer)

		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(19, true); }, voiceTimer + 6.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(7, true); }, voiceTimer + 8.0f)
		.AddEventKey([&]() { PlayVoice(6); }, voiceTimer += 9.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(17, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(1, true); }, voiceTimer)

		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(20, true); }, voiceTimer + 8.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(10, true); }, voiceTimer + 10.0f)
		.AddEventKey([&]() { PlayVoice(7); }, voiceTimer += 27.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(20, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(15, true); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(8); }, voiceTimer += 6.5f)
		.AddEventKey([&]() { PlaySound(0); mRenderParticleEffect = true; }, voiceTimer += 2.5f)
		.AddEventKey([&]() { mRenderParticleEffect = false; mCharacter.transform.position.y = 0.0f; mCharacterAnimator.PlayAnimation(0, false); }, voiceTimer += 10.0f)
		.AddEventKey([&]() { mCharacter.transform.position.z -= 2.0f; mCharacterAnimator.PlayAnimation(1, false); }, voiceTimer += 2.0f)
		.AddEventKey([&]() { PlayVoice(9); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { PlayVoice(10); PlayVoice(11, 0.1f); PlayVoice(12, 0.8f); PlayVoice(13); mCharFollowAnim2 = true; mCharacterAnimator2.PlayAnimation(0, true); }, voiceTimer += 4.0f)
		.AddPositionKey(mCharacter2.transform.position, voiceTimer)
		.AddPositionKey(mCharacter2.transform.position + Vector3{ 0, 0, 5 }, voiceTimer + 4.0f)
		.AddEventKey([&]() { PlayVoice(14); PlayVoice(15, 0.1f); mCharacterAnimator.PlayAnimation(9, true); mCharacterAnimator2.PlayAnimation(5, true); mCharFollowAnim2 = false; }, voiceTimer += 6.5f)
		.AddEventKey([&]() { PlayVoice(16); }, voiceTimer += 17.5f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(13, false); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(14, false); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(15, true); }, voiceTimer + 1.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(20, true); }, voiceTimer + 1.0f)
		.AddEventKey([&]() { PlayVoice(17); }, voiceTimer += 3.0)
		.AddEventKey([&]() { mCharacter.transform.position.z += 3.0f; mCharacterAnimator.PlayAnimation(10, false); }, voiceTimer + 1.3f)
		.AddEventKey([&]() { mCharacter.transform.position.z -= 4.0f; mCharacterAnimator.PlayAnimation(3, false); }, voiceTimer + 2.5f)
		.AddEventKey([&]() { mCharacter2.transform.position.y -= 1.0f; mCharacterAnimator2.PlayAnimation(6, true); }, voiceTimer + 2.5f + 0.5f)
		.AddEventKey([&]() { PlayVoice(18); }, voiceTimer += 5.0f)
		//.AddEventKey([&]() { mCharacter2.transform.position.y -= 1.0f; mCharacterAnimator2.PlayAnimation(6, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacter.transform.position.z += 1.5f; mCharacterAnimator.PlayAnimation(1, false); }, voiceTimer + 5.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(20, true); }, voiceTimer + 6.5f)
		.AddEventKey([&]() { PlayVoice(19); }, voiceTimer += 10.0f)
		.AddEventKey([&]() { mCharacter2.transform.position.y = 0.0f; mCharacterAnimator2.PlayAnimation(0, true); }, voiceTimer + 13.0f)
		.AddEventKey([&]() { PlayVoice(10); PlayVoice(11, 0.1f); PlayVoice(12, 0.8f); PlayVoice(13); mCharFollowAnim2 = true; }, voiceTimer + 13.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(-1, true); }, voiceTimer + 14.0f)
		.AddPositionKey({ 0.0f, 0.0f, 0.5f }, voiceTimer + 15.0f)
		.AddEventKey([&]() { StopVoice(10); StopVoice(11); StopVoice(12); StopVoice(13); }, voiceTimer + 15.0f)
		.AddEventKey([&]() { PlayVoice(20, 0.6f); }, voiceTimer += 16.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(9, true); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(21); }, voiceTimer += 12.0f)
		.AddEventKey([&]() { PlayVoice(22, 0.1f); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(12, true); mCharFollowAnim2 = true; }, voiceTimer)
		.AddPositionKey({ 0.0f, 0.0f, 0.5f }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(6, false); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(7, false); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(8, false); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(5, false); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { PlayVoice(23); }, voiceTimer += 5.0f)
		.AddEventKey([&]() { PlayVoice(31, 0.2f); }, voiceTimer += 2.0f)
		.AddEventKey([&]() { PlayVoice(32, 0.2f); }, voiceTimer += 4.0f)
		.AddEventKey([&]() { PlayVoice(33, 0.2f); }, voiceTimer += 3.0f)
		.AddEventKey([&]() { PlayVoice(34, 0.2f); }, voiceTimer += 3.0f)
		.AddEventKey([&]() { PlayVoice(35, 0.2f); }, voiceTimer += 3.0f)
		.AddEventKey([&]() { PlayVoice(36, 0.2f); }, voiceTimer += 3.0f)
		.AddEventKey([&]() { PlayVoice(37, 0.2f); }, voiceTimer += 3.0f)
		.AddEventKey([&]() { PlayVoice(38, 0.2f); }, voiceTimer += 3.0f)
		.AddEventKey([&]() { PlayVoice(39, 0.2f); }, voiceTimer += 3.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(21, false); }, voiceTimer += 3.5f)
		.AddEventKey([&]() { PlayVoice(24); }, voiceTimer += 0.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(20, true); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(15, true); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(25); }, voiceTimer += 4.0f)
		.AddEventKey([&]() { PlayVoice(26); }, voiceTimer += 8.0f)
		.AddEventKey([&]() { PlayVoice(27); }, voiceTimer += 4.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(11, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(12, true); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(20, 0.6f); }, voiceTimer += 4.5f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(9, true); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(-1, true); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(10); PlayVoice(11, 0.1f); PlayVoice(12, 0.8f); PlayVoice(13); }, voiceTimer)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(0, true); }, voiceTimer += 8.0f)
		.AddEventKey([&]() { PlayVoice(10); PlayVoice(11, 0.1f); PlayVoice(12, 0.8f); PlayVoice(13); }, voiceTimer + 0.01)
		//.AddEventKey([&]() { StopVoice(10); StopVoice(11); StopVoice(12); StopVoice(13); }, voiceTimer + 4.0f)
		.AddEventKey([&]() { PlayVoice(29); }, voiceTimer += 4.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(24, true); }, voiceTimer += 4.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(23, false); }, voiceTimer += 4.0f)
		.AddEventKey([&]() { mCharacterAnimator2.PlayAnimation(7, false); }, voiceTimer)
		.AddEventKey([&]() { PlayVoice(10); PlayVoice(11, 0.1f); PlayVoice(12, 0.8f); PlayVoice(13); }, voiceTimer += 1.0f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(24, true); }, voiceTimer += 2.0f)
		.Build();

	float cameraPositionTimer = 0.0f;
	// Control the camera from this
	mCameraAnimation = AnimationBuilder()
		.AddPositionKey(mCamera.GetPosition(), cameraPositionTimer)	// Add same position keys if you want to keep the camera at the exact position for a while
		//.AddEventKey([&]() {mCameraFollow = true; }, cameraPositionTimer + 0.01)
		.AddPositionKey(mCamera.GetPosition(), cameraPositionTimer += 35.0f)
		.AddPositionKey({ -0.1f, 1.7f, 4.5f }, cameraPositionTimer += 0.3f)
		//.AddEventKey([&]() {mCameraFollow = false; }, cameraPositionTimer)
		.Build();

	float cameraLootAtTimer = 0.0f;
	// Set camera look at animation
	mCameraLookAtAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f, 1.0f, 0.0f }, cameraLootAtTimer)		// Do John Cena intro
		//.AddEventKey([&]() {mCameraSetLookAt = true; }, cameraLootAtTimer + 0.01)
		.AddPositionKey({ 0.0f, 1.0f, 0.0f }, cameraLootAtTimer += 0.7f)
		.AddPositionKey({ 0.0f, 1.0f, 5.0f }, cameraLootAtTimer += 0.3f)
		//.AddEventKey([&]() {mCameraSetLookAt = false; }, cameraLootAtTimer)
		.AddPositionKey({ 0.0f, 1.0f, 5.0f }, cameraLootAtTimer += 1.0f)
		//.AddEventKey([&]() {mCameraSetLookAt = true; }, cameraLootAtTimer)
		.AddPositionKey({ 0.0f, 1.5f, 5.0f }, cameraLootAtTimer += 3.0f)
		.AddEventKey([&]() {mCameraSetLookAt = false; }, cameraLootAtTimer)
		.Build();

	mParticleSystemEffect.Initialize();
	mParticleSystemEffect.SetCamera(mCamera);

	ParticleSystemInfo info;
	info.textureId = TextureCache::Get()->LoadTexture("memes/Tumbleweed.png");
	int maxParticles = 100;
	info.particlesPerEmit = { 1, 4 };
	info.delay = 1.0f;
	info.lifeTime = FLT_MAX;
	info.timeBetweenEmit = { 0.2f, 0.4f };
	info.spawnAngle = { -90.0f,90.0f };
	info.spawnSpeed = { 1.0f, 5.0f };
	info.spawnLifeTime = { 0.5f, 2.0f };
	info.spawnDirection = Math::Vector3::YAxis;
	info.spawnPosition = Math::Vector3::Zero;
	info.startScale = { { 3.0f, 3.0f, 3.0f }, { 3.0f, 3.0f, 3.0f } };
	info.endScale = { { 3.0f, 3.0f, 3.0f }, { 3.0f, 3.0f, 3.0f } };
	info.startColor = { Colors::White, Colors::White };
	info.endColor = { Colors::White, Colors::White };
	mParticleSystem.Initialize(info);

	mAnimationTime = 0;
}

void Test()
{

}

void GameState::Terminate()
{
	mParticleSystem.Terminate();
	mParticleSystemEffect.Terminate();
	mCharacter2.Terminate();
	mCharacter.Terminate();
	mCube.Terminate();
	mGround.Terminate();
	mStandardEffect.Terminate();
}

float spin = 0.0f;
void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	mParticleSystem.Update(deltaTime);

	if (mAnimation.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mAnimation.PlayEvent(prevTime, mAnimationTime + deltaTime);

		//while (mAnimationTime > mAnimation.GetDuration())
		//{
		//	mAnimationTime -= mAnimation.GetDuration();	// Simple loop
		//}
	}

	if (mCameraAnimation.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mCameraAnimation.PlayEvent(prevTime, mAnimationTime + deltaTime);
	}

	if (mCameraLookAtAnimation.GetDuration() > 0.0f)
	{
		float prevTime = mAnimationTime;
		mCameraLookAtAnimation.PlayEvent(prevTime, mAnimationTime + deltaTime);
	}

	if (mCharFollowAnim1)
	{
		mCharacter.transform.position = mAnimation.GetTransform(mAnimationTime).position;
	}

	if (mCharFollowAnim2)
	{
		mCharacter2.transform.position = mAnimation.GetTransform(mAnimationTime).position;
	}

	mAnimationTime += deltaTime;

	mCharacterAnimator.Update(deltaTime);
	mCharacterAnimator2.Update(deltaTime);
	spin += deltaTime * 10;
	//mCharacter2.transform.rotation = Quaternion::CreateFromYawPitchRoll(0.0f, spin, 0.0f);
}

void GameState::UpdateCamera(float deltaTime)
{
	if (mCameraFollow)
	{
		mCamera.SetPosition(mCameraAnimation.GetTransform(mAnimationTime).position);
	}

	if (mCameraSetLookAt)
	{
		mCamera.SetLookAt(mCameraLookAtAnimation.GetTransform(mAnimationTime).position);
	}

	//LOG("%f %f %f", mCamera.GetPosition().x, mCamera.GetPosition().y, mCamera.GetPosition().z);
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
	mAnimationIndex1++;
	if (mAnimationIndex1 >= mCharacterAnimator.GetAnimationCount())
	{
		mAnimationIndex1 = 0;
	}
	mCharacterAnimator.PlayAnimation(mAnimationIndex1, true);
}

void GameState::PlaySound(int index, float volume)
{
	ASSERT(index < mSoundIds.size(), "Index out of range");
	SoundEffectManager::Get()->Play(mSoundIds[index], volume);
}

void GameState::PlayVoice(int index, float volume)
{
	ASSERT(index < mVoiceIds.size(), "Index out of range");
	SoundEffectManager::Get()->Play(mVoiceIds[index], volume);
}

void GameState::StopVoice(int index)
{
	ASSERT(index < mVoiceIds.size(), "Index out of range");
	SoundEffectManager::Get()->Stop(mVoiceIds[index]);
}

void GameState::SetLookAt(const SumEngine::Event& e, SumEngine::Math::Vector3 direction) const
{
	LOG("Set Look At called");
}

bool checkBox = true;

void GameState::Render()
{
	//mCharacter2.transform.rotation = mCameraAnimation.GetTransform(mAnimationTime).rotation;
	mStandardEffect.Begin();
	mStandardEffect.Render(mGround);
	mStandardEffect.Render(mCube);
	if (mRenderChar1)
		mStandardEffect.Render(mCharacter);
	if (mRenderChar2)
		mStandardEffect.Render(mCharacter2);
	//mStandardEffect.Render(mFish);
	mStandardEffect.End();

	mParticleSystemEffect.Begin();
	if (mRenderParticleEffect)
	{
		mParticleSystem.Render(mParticleSystemEffect);
	}
	mParticleSystemEffect.End();
}

SumEngine::Math::Vector3 cameraPos = SumEngine::Math::Vector3::Zero;
SumEngine::Math::Vector3 cameraDir = SumEngine::Math::Vector3::Zero;
int index = -1;
float volume = 1.0f;
bool stopAudio = false;
bool restartAudio = false;
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
		if (ImGui::DragInt("AnimIndex", &mAnimationIndex1, 1, -1, maxAnimations - 1))
		{
			mCharacterAnimator.PlayAnimation(mAnimationIndex1, true);
		}

		int maxAnimations2 = mCharacterAnimator2.GetAnimationCount();
		if (ImGui::DragInt("AnimIndex2", &mAnimationIndex2, 1, -1, maxAnimations2 - 1))
		{
			mCharacterAnimator2.PlayAnimation(mAnimationIndex2, true);
		}

		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Position##Camera", &cameraPos.x, 0.01f))
		{
			mCamera.SetPosition(cameraPos);
		}

		if (ImGui::DragFloat3("Direction##Camera", &cameraDir.x, 0.01f))
		{
			mCamera.SetLookAt(cameraDir);
		}
	}

	if (ImGui::Checkbox("TurnOffVoice", &stopAudio))
	{
		StopVoice(index);
	}

	if (ImGui::Checkbox("RestartVoice", &restartAudio))
	{
		PlayVoice(index, volume);
	}

	int max = mVoiceIds.size();

	if (ImGui::DragInt("VoiceIndex", &index, 1, 0, max))
	{
		PlayVoice(index, volume);
	}

	ImGui::DragFloat("VoiceVolume", &volume, 0.01f, 0.0f, 1.0f);

	ImGui::Text("Timer: %.3f", mAnimationTime);

	ImGui::End();
}
