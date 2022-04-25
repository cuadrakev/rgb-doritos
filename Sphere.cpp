#include "Sphere.h"

Sphere::Sphere(float radius, int sides, int levels)
{
	levels = levels - 1;
	vSize = sides * levels + 2;
	tSize = 2 * sides * levels;
	verts = new Vertex[vSize];
	indices = new int3[tSize];

	verts[vSize - 1].pos = float3(0, -radius, 0);
	verts[vSize - 2].pos = float3(0, radius, 0);

	float heightLvl = 2 * radius / (levels + 1);

	for (int j = 0; j < levels; j++)
	{
		for (int i = 0; i < sides; i++)
		{
			//float height = (float)(j + 1) * heightLvl;
			//float horiAngle = std::asin((radius - height)/radius);
			float horiAngle = M_PI * (float)(j + 1) / ((levels+1));
			float height = radius * (1.0f - std::cos(horiAngle));
			float distToAxis = radius * std::sin(horiAngle);
			float angle = 2.0f * M_PI * i / sides;
			verts[i + j * sides].pos = float3(distToAxis * std::cos(angle), height - radius, distToAxis * std::sin(angle));
		}
	}

	for (int j = 0; j < levels; j++)
	{
		for (int i = 0; i < sides; i++)
		{
			if (j != 0)
				indices[i + j * sides] = int3(i + j * sides, (i + 1) % sides + j * sides, (i + 1) % sides + (j - 1) * sides);
			else
				indices[i] = int3(i, (i + 1) % sides, vSize - 1);

			if (j != levels - 1)
				indices[i + j * sides + levels * sides] = int3((i + 1) % sides + j * sides, i + j * sides, i + (j + 1) * sides);
			else
				indices[i + j * sides + levels * sides] = int3((i + 1) % sides + j * sides, i + j * sides, vSize - 2);

		}
	}
}
