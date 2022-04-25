#pragma once

#include "math_all.h"

class VertexProcessor
{
public:
	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;

	float3 viewPos;
	float3 viewDir;

	VertexProcessor();

	void setPerspective(float fovy, float aspect, float near, float far);

	void setLookat(float3 eye, float3 center, float3 up);

	void translate(float3 t);

	void scale(float3 s);

	void rotate(float angle, float3 axis);

	void resetTransform();

	float4x4 getObj2Proj() { return view2proj * world2view * obj2world; }

	float3x3 getNormalMatrix();
};

