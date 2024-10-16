#pragma once

#include "MeshBuffer.h"
#include "TextureCache.h"
#include "Transform.h"
#include "Material.h"

namespace SumEngine::Graphics
{

	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;

		Material material;
		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;
	};
}