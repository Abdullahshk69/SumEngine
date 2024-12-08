#include "Precompiled.h"
#include "WaterEffect.h"

#include "VertexTypes.h"
#include "Camera.h"
#include "RenderObject.h"

using namespace SumEngine;
using namespace SumEngine::Graphics;

void WaterEffect::Initialize()
{
	// water shader will have a consistent shaderFile
	std::filesystem::path shaderFile = L"../../Assets/Shaders/WaterWaves.fx";
	mVertexShader.Initialize<Vertex>(shaderFile);
	mPixelShader.Initialize(shaderFile);
	mTransformBuffer.Initialize();
	mSettingsBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void WaterEffect::Terminate()
{
	mSampler.Terminate();
	mSettingsBuffer.Terminate();
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void WaterEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);

	mTransformBuffer.BindVS(0);
	mSettingsBuffer.BindVS(1);
}

void WaterEffect::End()
{

}

void WaterEffect::Update(float deltaTime)
{
	mSettingsData.waveTime += deltaTime;
}

void WaterEffect::Render(const RenderObject& renderObject)
{
	SettingsData settingsData;
	settingsData.strength = mSettingsData.strength;
	settingsData.speed = mSettingsData.speed;
	settingsData.frequency = mSettingsData.frequency;

	const Math::Matrix4 matWorld = renderObject.transform.GetMatrix4();
	const Math::Matrix4 matView = mCamera->GetViewMatrix();
	const Math::Matrix4 matProj = mCamera->GetProjectionMatrix();

	const Math::Matrix4 matFinal = matWorld * matView * matProj;

	WaterTransform waterTransform;
	waterTransform.wvp = Transpose(matFinal);
	mSettingsBuffer.Update(settingsData);
}

void WaterEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void WaterEffect::SetLightCamera(const Camera& camera)
{
	mLightCamera = &camera;
}

void WaterEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void WaterEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("Waves", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Strength#Waves", &mSettingsData.strength);
		ImGui::DragFloat("Speed#Waves", &mSettingsData.speed);
		ImGui::DragFloat("Frequency#Waves", &mSettingsData.frequency);
	}
}
