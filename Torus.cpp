#include "Torus.h"

Torus::Torus(float innerRad, float outerRad, int poloidSegments, int toroidSegments)
{
	vSize = poloidSegments * toroidSegments;
	tSize = 2 * poloidSegments * toroidSegments;
	verts = new Vertex[vSize];
	indices = new int3[tSize];

	for (int j = 0; j < poloidSegments; j++)
	{
		float outerAngle = 2.0f * M_PI * j / poloidSegments;
		float3 tubeCenter = float3(outerRad * std::cos(outerAngle), 0, outerRad * std::sin(outerAngle));

		for (int i = 0; i < toroidSegments; i++)
		{
			float innerAngle = 2.0f * M_PI * i / toroidSegments;
			float3 circlePoints = float3(std::sin(innerAngle) * std::cos(outerAngle), 
										std::cos(innerAngle), 
										std::sin(innerAngle) * std::sin(outerAngle)) * innerRad;
			verts[i + j * toroidSegments].pos = tubeCenter + circlePoints;
		}
	}

	for (int j = 0; j < poloidSegments; j++)
	{
		int ts = toroidSegments;
		for (int i = 0; i < toroidSegments; i++)
		{
			indices[i + j * ts] = int3((i + 1) % ts + j * ts, i + j * ts, ((i+1) % ts + (j + 1) * ts) % vSize);
			indices[i + j * ts + poloidSegments * ts] = int3(i + j * ts, (i + 1) % ts + j * ts, (i + (j - 1) * ts + vSize) % vSize);
		}
	}
}