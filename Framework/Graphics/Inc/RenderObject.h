#pragma once

#include "MeshBuffer.h"
#include "TextureCache.h"
#include "Transform.h"

namespace SumEngine::Graphics
{

	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;
		TextureId diffuseTextureId;
	};
}