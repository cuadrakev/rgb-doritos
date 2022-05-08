#include "Mesh.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

void Mesh::draw(Rasterizer* rasterizer, VertexProcessor* vp)
{
	for (int t = 0; t < tSize; t++)
	{
		Triangle triangle;
		triangle.a = verts[indices[t].a];
		triangle.b = verts[indices[t].b];
		triangle.c = verts[indices[t].c];

		rasterizer->drawTriangle(triangle.a, triangle.b, triangle.c, meshColor);
	}
}

void Mesh::drawGourard(Rasterizer* rasterizer, VertexProcessor* vp)
{
	for (int t = 0; t < tSize; t++)
	{
		Triangle triangle;
		triangle.a = verts[indices[t].a];
		triangle.b = verts[indices[t].b];
		triangle.c = verts[indices[t].c];

		float3 colorA;
		float3 colorB;
		float3 colorC;

		for (Light* l : rasterizer->lightsList)
		{
			colorA += l->Calculate(&triangle.a, vp);
			colorB += l->Calculate(&triangle.b, vp);
			colorC += l->Calculate(&triangle.c, vp);
		}

		colorA.saturate();
		colorB.saturate();
		colorC.saturate();

		rasterizer->drawTriangle(triangle.a.pos, triangle.b.pos, triangle.c.pos, colorA, colorB, colorC);

		//rasterizer->drawTriangle(triangle.a, triangle.b, triangle.c, 0xFFFFFF);
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
