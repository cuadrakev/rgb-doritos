#include "DirectionalLight.h"
#include <cmath>

float3 DirectionalLight::Calculate(Fragment* frag, VertexProcessor* vp)
{
    float3x3 normalMat = vp->getNormalMatrix();

    float4x4 worldMat = vp->obj2world;

    float3 viewDir = vp->viewDir;

    float3 color = float3(1, 1, 1);

    float3 lightDir = (pos).Normalize();

    float3 normal = (normalMat * frag->normal).Normalize();

    float dot = lightDir.DotProduct(normal);

    float diffuse = dot * (dot > 0.0f);

    float3 reflect = -lightDir.Reflect(normal);

    float dot2 = reflect.DotProduct(viewDir);

    float specular = std::pow(dot2 * (dot2 > 0.0f), shiny);

    float3 fragCol = (amb + diff * diffuse + spec * specular) * color;

    fragCol.saturate();

    return fragCol;
}
