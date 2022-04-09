#include "VertexProcessor.h"

VertexProcessor::VertexProcessor()
{
	obj2world = float4x4::identity4x4();
	world2view = float4x4::identity4x4();
	view2proj = float4x4::identity4x4();
}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= M_PI / 360;
	float f = std::sin(fovy) / std::cos(fovy);

	view2proj.setColumn(0, float4(-f / aspect, 0, 0, 0));
	view2proj.setColumn(1, float4(0, -f, 0, 0));
	view2proj.setColumn(2, float4(0, 0, (far+near)/(near-far), 1));
	view2proj.setColumn(3, float4(0, 0, 2*far*near/(near-far), 0));
}

void VertexProcessor::setLookat(float3 eye, float3 center, float3 up)
{
	float3 f = eye - center;
	f = f.Normalize();
	up = up.Normalize();
	float3 s = f.CrossProduct(up);
	float3 u = s.CrossProduct(f);

	world2view.setColumn(0, float4(s[0], u[0], -f[0], 0));
	world2view.setColumn(1, float4(s[1], u[1], -f[1], 0));
	world2view.setColumn(2, float4(s[2], u[2], -f[2], 0));
	world2view.setColumn(3, float4(0, 0, 0, 1));
	float4x4 m = float4x4::identity4x4();
	m.setColumn(3, float4(eye));
	world2view = world2view * m;
}

void VertexProcessor::translate(float3 t)
{
	float4x4 transMatrix = float4x4::identity4x4();
	transMatrix.setColumn(3, float4(t));

	obj2world = transMatrix * obj2world;
}

void VertexProcessor::scale(float3 s)
{
	float3x3 scaleMatrix(float3(s.x, 0, 0),
		float3(0, s.y, 0),
		float3(0, 0, s.z));

	obj2world = float4x4(scaleMatrix) * obj2world;
}

void VertexProcessor::rotate(float angle, float3 axis)
{
	axis = axis.Normalize();

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	float rads = mathlib::angle2rad(angle);

	float4x4 rotMatrix;

	float s = std::sin(rads);
	float c = std::cos(rads);
	float ccomp = 1 - c;

	rotMatrix.setColumn(0, float4(
		x * x * ccomp + c, 
		x * y * ccomp + z * s,
		x * z * ccomp - y * s,
		0));
	rotMatrix.setColumn(1, float4(
		x * y * ccomp - z * s,
		y * y * ccomp + c,
		y * z * ccomp + x * s,
		0));
	rotMatrix.setColumn(2, float4(
		x * z * ccomp + y * s,
		y * z * ccomp - x * s,
		z * z * ccomp + c,
		0));
	rotMatrix.setColumn(3, float4(0,0,0,1));

	obj2world = rotMatrix * obj2world;
}

void VertexProcessor::resetTransform()
{
	obj2world = float4x4::identity4x4();
}