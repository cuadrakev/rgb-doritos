#pragma once
#include "float3.h"
#include "int3.h"
#include "Rasterizer.h"
#include "VertexProcessor.h"
#include "Light.h"

//struct Vertex {
//	float3 pos;
//	float3 normal;
//};

struct Triangle {
	Vertex a, b, c;
};

class Mesh
{
protected:

	int vSize;
	int tSize;
	int3* indices;
	Vertex* verts;

public:

	~Mesh() { delete[] indices; delete[] verts; }
	void draw(Rasterizer* rasterizer, VertexProcessor* vp);
	void makeNormals();
};

