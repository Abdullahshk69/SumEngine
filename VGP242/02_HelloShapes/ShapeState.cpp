#include "ShapeState.h"

using namespace SumEngine;
using namespace SumEngine::Math;
using namespace SumEngine::Graphics;
using namespace SumEngine::Core;
using namespace SumEngine::Input;

void ShapeState::Initialize()
{
	// create a simple shape in NDC space (-1/1, -1/1, 0/1)
	// triangle
	CreateShape();

	auto device = GraphicsSystem::Get()->GetDevice();
	//=================================================
	// create a vertex buffer
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = mVertices.data();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer");

	//=================================================
	// create a vertex shader
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoColor.fx";

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
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

	//=================================================
	// create a pixel shader

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
	mVertices.clear();
	SafeRelease(mPixelShader);
	SafeRelease(mInputLayout);
	SafeRelease(mVertexShader);
	SafeRelease(mVertexBuffer);
}

void ShapeState::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();

	context->VSSetShader(mVertexShader, nullptr, 0);
	context->IASetInputLayout(mInputLayout);
	context->PSSetShader(mPixelShader, nullptr, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);	// how far apart are they
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->Draw((UINT)mVertices.size(), 0);
}

// Triangle Shape
void TriangleShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::UP))
	{
		MainApp().ChangeState("TriforceShapeState");
	}
}

void TriangleShapeState::CreateShape()
{
	mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Red });
	mVertices.push_back({ { 0.0f, 0.75f, 0.0f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.0f, 0.0f }, Colors::Blue });
}

// Square Shape
void SquareShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("TriangleShapeState");
	}
}

void SquareShapeState::CreateShape()
{
	mVertices.push_back({ { -0.5f, -0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.0f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f }, Colors::Blue });

	mVertices.push_back({ { -0.5f, -0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f }, Colors::Green });

}

void TriforceShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("DiamondShapeState");
	}
}

void TriforceShapeState::CreateShape()
{
	// Triangle 1
	mVertices.push_back({ { -1.0f, 0.0f, 0.0f }, Colors::Red });
	mVertices.push_back({ { -0.75f, 0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Red });

	// Triangle 2
	mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { -0.25f, 0.5f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { 0.0f, 0.0f, 0.0f }, Colors::Blue });

	// Triangle 3
	mVertices.push_back({ { -0.75f, 0.5f, 0.0f }, Colors::Green });
	mVertices.push_back({ { -0.5f, 1.0f, 0.0f }, Colors::Green });
	mVertices.push_back({ { -0.25f, 0.5f, 0.0f }, Colors::Green });
}

void DiamondShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("HatShapeState");
	}
}

void DiamondShapeState::CreateShape()
{
	// Center Triangle
	mVertices.push_back({ { 0.0f, -0.5f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { -0.25f, 0.5f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { 0.25f, 0.5f, 0.0f }, Colors::Blue });

	// Left side Triangle
	mVertices.push_back({ { 0.0f, -0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ { -0.5f, 0.5f, 0.0f }, Colors::Red });
	mVertices.push_back({ { 0.25f, 0.5f, 0.0f }, Colors::Red });

	// Right side Triangle
	mVertices.push_back({ { 0.0f, -0.5f, 0.0f }, Colors::Green });
	mVertices.push_back({ { 0.25f, 0.5f, 0.0f }, Colors::Green });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f }, Colors::Green });

	// Top Middle
	mVertices.push_back({ { -0.25f, 0.5f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.0f, 1.0f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.25f, 0.5f, 0.0f }, Colors::Purple });

	// Top Right Base Down
	mVertices.push_back({ { 0.25f, 0.5f, 0.0f }, Colors::Brown });
	mVertices.push_back({ { 0.375f, 1.0f, 0.0f }, Colors::Brown });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f }, Colors::Brown });

	// Top Right Base Up
	mVertices.push_back({ { 0.25f, 0.5f, 0.0f }, Colors::Pink });
	mVertices.push_back({ { 0.0f, 1.0f, 0.0f }, Colors::Pink });
	mVertices.push_back({ { 0.375f, 1.0f, 0.0f }, Colors::Pink });

	// Top Left Base Down
	mVertices.push_back({ { -0.5f, 0.5f, 0.0f }, Colors::Magenta });
	mVertices.push_back({ { -0.375f, 1.0f, 0.0f }, Colors::Magenta });
	mVertices.push_back({ { -0.25f, 0.5f, 0.0f }, Colors::Magenta });

	// Top Left Base Up
	mVertices.push_back({ { -0.25f, 0.5f, 0.0f }, Colors::Orange });
	mVertices.push_back({ { -0.375f, 1.0f, 0.0f }, Colors::Orange });
	mVertices.push_back({ { 0.0f, 1.0f, 0.0f }, Colors::Orange });
}

void StarShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("TriforceShapeState");
	}
}

void StarShapeState::CreateShape()
{

	//x = cos(angle);
	//y = sin(angle);
	
	// Outer Triangles
	// 1
	mVertices.push_back({ { -0.125f, 0.5f, 0.0f }, Colors::Pink });
	mVertices.push_back({ { 0.0f, 1.0f, 0.0f }, Colors::Pink });
	mVertices.push_back({ { 0.125f, 0.5f, 0.0f }, Colors::Pink });

	// 2
	/*mVertices.push_back({ { -0.2f, 0.25f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { -0.5f, 0.5f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { -0.125f, 0.5f, 0.0f }, Colors::Blue });*/

	// 3

	// 4

	// 5

	// Inner Triangles
	// 6
	mVertices.push_back({ { -0.2f, 0.0f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { -0.125f, 0.375f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.125f, 0.375f, 0.0f }, Colors::Purple });

	// 7
	mVertices.push_back({ { 0.0f, -0.25f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { -0.2f, 0.0f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.125f, 0.5f, 0.0f }, Colors::Purple });
	
	// 8
	mVertices.push_back({ { 0.0f, -0.25f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.125f, 0.5f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.2f, 0.0f, 0.0f }, Colors::Purple });
}

void HatShapeState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("TriforceShapeState");
	}
}

void HatShapeState::CreateShape()
{
	// Top Triangles
	mVertices.push_back({ { -0.5f, -0.2f, 0.0f }, Colors::Brown });
	mVertices.push_back({ { -0.5f, 0.5f, 0.0f }, Colors::Brown });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f }, Colors::Brown });

	mVertices.push_back({ { -0.5f, -0.2f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, 0.5f, 0.0f }, Colors::Blue });
	mVertices.push_back({ { 0.5f, -0.2f, 0.0f }, Colors::Blue });

	
	// Bottom Triangles
	mVertices.push_back({ { -0.5f - 0.2f, -0.5f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { -0.5f - 0.2f, -0.2f, 0.0f }, Colors::Purple });
	mVertices.push_back({ { 0.5f + 0.2f, -0.2f, 0.0f }, Colors::Purple });

	mVertices.push_back({ { -0.5f - 0.2f, -0.5f, 0.0f }, Colors::Magenta });
	mVertices.push_back({ { 0.5f + 0.2f, -0.2f, 0.0f }, Colors::Magenta });
	mVertices.push_back({ { 0.5f + 0.2f, -0.5f, 0.0f }, Colors::Magenta });
}
