#include "Mesh.h"
#include "DirectionalLight.h"
#include "PointLight.h"

void Mesh::draw(Rasterizer* rasterizer, VertexProcessor* vp)
{
	for (int t = 0; t < tSize; t++)
	{
		Triangle triangle;
		triangle.a = verts[indices[t].a];
		triangle.b = verts[indices[t].b];
		triangle.c = verts[indices[t].c];

		DirectionalLight l(float3(0.5f, -0.5f, -0.0f), float3(0.1f, 0.1f, 0.1f), float3(0.0f, 0.0f, 0.5f), float3(0.5f, 0.0f, 0.0f), 32);
		PointLight p(float3(-0.0f, 2.0f, -0.0f), float3(0.0f, 0.0f, 0.2f), float3(0.0f, 0.0f, 0.0f), float3(0.5f, 0.0f, 0.0f), 32);

		float3 colorA = l.Calculate(&triangle.a, vp) + p.Calculate(&triangle.a, vp);
		float3 colorB = l.Calculate(&triangle.b, vp) + p.Calculate(&triangle.b, vp);
		float3 colorC = l.Calculate(&triangle.c, vp) + p.Calculate(&triangle.c, vp);

		colorA.saturate();
		colorB.saturate();
		colorC.saturate();

		rasterizer->drawTriangle(triangle.a.pos, triangle.b.pos, triangle.c.pos, colorA, colorB, colorC);
	}
}

void Mesh::makeNormals()
{
	for (int i = 0; i < vSize; i++)
	{
		verts[i].normal = float3();
	}

	for (int i = 0; i < tSize; i++)
	{
		float3 cross = (verts[indices[i].c].pos - verts[indices[i].a].pos).CrossProduct(
			verts[indices[i].b].pos - verts[indices[i].a].pos
		);

		cross = cross.Normalize();

		verts[indices[i].a].normal += cross;
		verts[indices[i].b].normal += cross;
		verts[indices[i].c].normal += cross;

		for (int i = 0; i < vSize; i++)
		{
			verts[i].normal = verts[i].normal.Normalize();
		}
	}
}
