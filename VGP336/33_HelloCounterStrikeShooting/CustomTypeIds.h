#pragma once

#include <SumEngine/Inc/SumEngine.h>

enum class CustomComponentId
{
	CS_CharacterMovement = static_cast<uint32_t>(SumEngine::ComponentId::Count),
	CS_FPSCamera,
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(SumEngine::ServiceId::Count),
};