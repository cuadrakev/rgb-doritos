#include "PointLight.h"
#include <cmath>

float3 PointLight::Calculate(Fragment* frag, VertexProcessor* vp)
{
    float3x3 normalMat = vp->getNormalMatrix();

    float4x4 worldMat = vp->obj2world;

    float3 color = float3(1, 1, 1);

    float3 fragPos = worldMat * frag->pos;

    float3 lightDir = ((fragPos-pos)).Normalize();

    float3 normal = normalMat * frag->normal;

    float3 reflect = lightDir.Reflect(normal);

    float dot = lightDir.DotProduct(normal);

    float diffuse = (dot > 0.0f) * dot;

    float dot2 = reflect.DotProduct(lightDir);

    float specular = 0;// std::pow(dot2 * (dot2 > 0.0f), shiny);

    float3 fragCol = (amb + diff * diffuse + spec * specular) * color;

    fragCol.saturate();

    return fragCol;
}