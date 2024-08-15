#pragma once

#include "MeshTypes.h"

namespace SumEngine::Graphics
{
	class MeshBuilder
	{
	public:
		// Cube
		static MeshPC CreateCubePC(float size);

		// Rectangle
		static MeshPC CreateRectPC(float width, float length, float height);
	
		// Plane
		static MeshPC CreatePlanePC(int numRows, int numCols, float spacing);
		static MeshPX CreatePlanePX(int numRows, int numCols, float spacing);

		// Cylinder
		static MeshPC CreateCylinderPC(int slices, int rings);

		// Sphere
		static MeshPC CreateSpherePC(int slices, int rings, float radius);
	};
}