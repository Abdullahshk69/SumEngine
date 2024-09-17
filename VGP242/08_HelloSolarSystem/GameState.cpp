#include "GameState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;

const char* gDrawTypeNames[] =
{
	"None",
	"Sun",
	"Venus",
	"Earth",
	"Mars",
	"Jupiter",
	"Saturn",
	"Neptune",
	"Uranus",
	"Pluto",
	"Galaxy"
};

const char* cTextureLocations[] =
{
	"planets/sun.jpg",
	"planets/mercury.jpg",
	"planets/venus.jpg",
	"planets/earth.jpg",
	"planets/mars.jpg",
	"planets/jupiter.jpg",
	"planets/saturn.jpg",
	"planets/neptune.jpg",
	"planets/uranus.jpg",
	"planets/pluto.jpg",
	"skysphere/space.jpg"
};

namespace
{
	void CreatePlanets()
	{
		
	}
}

void GameState::Initialize()
{
	MeshPX meshes[(int)SolarSystem::Galaxy + 1];

	meshes[(int)SolarSystem::Sun] = MeshBuilder::CreateSpherePX(60, 60, 4.0f);
	MeshPX mesh = MeshBuilder::CreateSpherePX(60, 60, 1.0f);
	MeshPX mesh2 = MeshBuilder::CreateSpherePX(60, 60, 2.0f);

	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetAspectRatio(1.0f);

	mObjects[0].mMeshBuffer.Initialize<MeshPX>(mesh);
	mObjects[1].mMeshBuffer.Initialize<MeshPX>(mesh2);
	//mMeshBuffer.Initialize<MeshPX>(mesh);
	mConstantBuffer.Initialize(sizeof(Matrix4));
	//mConstantBuffer.Initialize(sizeof(Matrix4));

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	//mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);
	//mPixelShader.Initialize(shaderFile);

	/*for (int i = 0; i < (int)SolarSystem::End; i++)
	{
		mObjects[i].mDiffuseTexture.Initialize("../../Assets/Images/" + (std::string)cTextureLocations[i]);
	}*/

	mObjects[0].mDiffuseTexture.Initialize("../../Assets/Images/planets/earth/earth.jpg");
	mObjects[1].mDiffuseTexture.Initialize("../../Assets/Images/planets/jupiter.jpg");
	//mDiffuseTexture.Initialize("../../Assets/Images/planets/earth/earth.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	//mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	mRenderTarget.Terminate();
	mSampler.Terminate();
	mObjects[1].mDiffuseTexture.Terminate();
	mObjects[0].mDiffuseTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mObjects[0].mMeshBuffer.Terminate();
	mObjects[1].mMeshBuffer.Terminate();
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

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mObjects[0].mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);

	// constant buffer
	Matrix4 matWorld = Matrix4::Identity;
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	// mConstantBuffer.BindVS(0)
	// for(planet : planets)
	//{
	//	matWorld = planet.transform
	//  matFinal = matWorld * matView * matProj
	// wvp = Transpose(matFinal)
	// mContantBuffer.Update(&mvp)
	// //maybe bind again
	// planet.meshBuffer.Render()
	//}

	// mesh buffer
	mObjects[0].mMeshBuffer.Render();


	mObjects[1].mDiffuseTexture.BindPS(0);

	Matrix4 matWorld2 = Matrix4::Identity;
	Matrix4 matView2 = mCamera.GetViewMatrix();
	Matrix4 matProj2 = mCamera.GetProjectionMatrix();
	Matrix4 matFinal2 = matWorld2 * matView2 * matProj2;
	Matrix4 wvp2 = Transpose(matFinal2);

	mObjects[1].mMeshBuffer.Render();

	Matrix4 matWorld1 = Matrix4::Identity;
	Matrix4 matView1 = mRenderTargetCamera.GetViewMatrix();
	Matrix4 matProj1 = mRenderTargetCamera.GetProjectionMatrix();
	Matrix4 matFinal1 = matWorld1 * matView1 * matProj1;
	Matrix4 wvp1 = Transpose(matFinal1);
	mConstantBuffer.Update(&wvp1);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();
		mObjects[0].mMeshBuffer.Render();
	mRenderTarget.EndRender();
}

bool buttonValue = false;
int intValue = 0;
void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 256, 256 },
		{ 0, 0 },	//uv0
		{ 1, 1 },	//uv1
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });
	ImGui::End();
}

void PlanetPosition()
{

}
