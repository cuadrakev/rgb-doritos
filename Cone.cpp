#include "Cone.h"
#include "math_all.h"

Cone::Cone(float radius, float height, int sides)
{
	vSize = sides + 2;
	tSize = 2 * sides;
	verts = new Vertex[vSize];
	indices = new int3[tSize];

	verts[vSize - 1].pos = float3(0, 0, 0);
	verts[vSize - 2].pos = float3(0, -height, 0);

	for (int i = 0; i < sides; i++)
	{
		float angle = 2.0f * M_PI * i / sides;
		verts[i].pos = float3(radius * std::cos(angle), 0, radius * std::sin(angle));
	}

	for (int i = 0; i < sides; i++)
	{
		indices[i] = int3((i + 1) % sides, i, vSize - 1);
		indices[i+sides] = int3(i, (i + 1) % sides, vSize - 2);
		//indices[i + sides] = int3(0, 0, 0);
	}

}
