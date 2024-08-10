#include "ShapeState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;

void ShapeState::CreateShape()
{
	// Vertices for each face (6 for each)

	// front
	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Blue });

	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Green });

	// back
	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Green });

	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });

	// right
	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });

	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Green });

	// left
	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Green });

	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Green });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Blue });

	// top
	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });

	mVertices.push_back({ { -0.5f, 0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, 0.5f, -0.5f }, Colors::Green });

	// bottom
	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, -0.5f, 0.5f }, Colors::Green });

	mVertices.push_back({ { -0.5f, -0.5f, -0.5f }, Colors::Red });
	mVertices.push_back({ { 0.5f, -0.5f, -0.5f }, Colors::Green });
	mVertices.push_back({ { 0.5f, -0.5f, 0.5f }, Colors::Blue });
}

void ShapeState::Initialize()
{
	// create a simple shape in NDC space (-1/1, -1/1, 0/1)
	// triangle
	CreateShape();

	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());

	mConstantBuffer.Initialize(sizeof(Matrix4));

	auto device = GraphicsSystem::Get()->GetDevice();
	//=================================================
	// create a vertex buffer
	

	//=================================================
	// create a vertex shader
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize(shaderFile, VE_Position | VE_Color);

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Fialed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader
	);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex shader");

	//=================================================
	// create input layout
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
	vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	hr = device->CreateInputLayout(
		vertexLayout.data(),
		(UINT)vertexLayout.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout
	);
	ASSERT(SUCCEEDED(hr), "Failed to create input layout");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	mVertexShader
	mPixelShader.Initialize(shaderFile);

	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "Fialed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader
	);
	ASSERT(SUCCEEDED(hr), "Failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void ShapeState::Terminate()
{
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
	mVertexShader.Terminate();
	mVertices.clear();
	SafeRelease(mPixelShader);
}

float gRotationX = 0.0f;
float gRotationY = 0.0f;
void ShapeState::Update(float deltaTime)
{
	gRotationX += Math::Constants::HalfPi * deltaTime * 0.25f;
	gRotationY += Math::Constants::HalfPi * deltaTime * 0.5f;
}

void ShapeState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	mVertexShader.Bind();

	// vertex shader
	context->VSSetShader(mVertexShader, nullptr, 0);
	context->IASetInputLayout(mInputLayout);
	
	// pixel shader
	context->PSSetShader(mPixelShader, nullptr, 0);

	// constant buffer

	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	// mesh buffer
	mMeshBuffer.Render();
}
