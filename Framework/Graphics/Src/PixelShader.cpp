#include "Precompiled.h"
#include "PixelShader.h"
#include "GraphicsSystem.h"

using namespace SumEngine;
using namespace SumEngine::Graphics;

void PixelShader::Initialize(const std::filesystem::path& filePath)
{
	auto device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr = D3DCompileFromFile(
		filePath.c_str(),
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

void PixelShader::Terminate()
{
}

void PixelShader::Bind()
{
}
