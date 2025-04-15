#pragma once

#include "Common.h"

#include "App.h"
#include "AppState.h"
#include "Event.h"
#include "EventManager.h"

// Components
#include "Component.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "TransformComponent.h"

// Game Object
#include "GameObject.h"
#include "GameWorld.h"
#include "TypeIds.h"

// Services
#include "Service.h"

namespace SumEngine
{
	App& MainApp();
}