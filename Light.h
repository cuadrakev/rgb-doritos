#pragma once
#include "float3.h"
#include "VertexProcessor.h"

#define Fragment Vertex

struct Vertex {
	float3 pos;
	float3 normal;

	Vertex(float3 p, float3 n)
	{
		pos = p;
		normal = n;
	}

	Vertex()
	{
		pos = float3();
		normal = float3();
	}
};
//struct Fragment;

class Light
{
protected:
	float3 pos;
	float3 amb;
	float3 diff;
	float3 spec;
	float shiny;

public:
	Light(float3 pos, float3 amb, float3 diff, float3 spec, float shiny) 
		: pos(pos), amb(amb), diff(diff), spec(spec), shiny(shiny) {}
	virtual float3 Calculate(Fragment* frag, VertexProcessor* vp) = 0;
};

