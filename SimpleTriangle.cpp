#include "SimpleTriangle.h"

SimpleTriangle::SimpleTriangle()
{
	vSize = 3;
	tSize = 1;
	verts = new Vertex[3];
	indices = new int3[1];
	verts[0].pos = float3(-.5f, 0.f, 0.f);
	verts[1].pos = float3(0.f, .5f, 0.f);
	verts[2].pos = float3(.5f, 0.f, 0.f);
	indices[0] = int3(0, 1, 2);
}