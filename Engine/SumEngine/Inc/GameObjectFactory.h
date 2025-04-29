#pragma once

namespace SumEngine
{
	class GameObject;
	class GameWorld;

	namespace GameObjectFactory
	{
		void Make(const std::filesystem::path& templatePath, GameObject& gameObject, GameWorld& gameWorld);
		void OverrideDeserialize(const rapidjson::Value& value, GameObject& gameObject);
	}
}