#pragma once

#include <SumEngine/Inc/SumEngine.h>

enum class CustomComponentId
{
	CS_FPSCamera = static_cast<uint32_t>(SumEngine::ComponentId::Count),
	BaseGun,
	Pistol
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(SumEngine::ServiceId::Count),
};