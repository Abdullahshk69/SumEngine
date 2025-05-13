#pragma once

namespace SumEngine
{
	enum class ComponentId
	{
		Invalid,		// default value, not valid
		Transform,		// Transform component for location data
		Camera,			// contains the camera for viewing
		FPSCamera,		// move the camera with fps controls
		Mesh,			// adds a mesh shape to the game object
		Model,			// adds a model to the game object
		Animator,		// adds an animation controller to the game object
		RigidBody,		// adds a physics body shape to the game object
		SoundEffect,	// adds a sound effect to the object
		SoundBank,		// adds a group of sound effects to an object
		UIText,			// adds a UI text component
		UISprite,		// adds a sprite to the UI
		UIButton,		// adds a button to the UI
		Count			// last value, chain ids in custom components
	};

	enum class ServiceId
	{
		Invalid,		// default value, not valid
		Camera,			// manages the cameras in the world
		Render,			// renders renderobjects to the world
		Physics,		// manages the physics systems in the world
		UIRender,		// renders UI objects to the world
		Count			// last value, chain ids in custom services
	};
}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() { return static_cast<uint32_t>(id); }\
	uint32_t GetTypeId() const override { return StaticGetTypeId(); }