#include "SpotLight.h"

float3 SpotLight::Calculate(Fragment* frag, VertexProcessor* vp)
{
    float3x3 normalMat = vp->getNormalMatrix();

    float4x4 worldMat = vp->obj2world;

    float3 color = float3(1, 1, 1);

    float3 fragPos = worldMat * frag->pos;

    float3 lightDir = ((fragPos - pos)).Normalize();

    float3 viewDir = vp->viewDir;

    float3 normal = normalMat * frag->normal;

    float dot = lightDir.DotProduct(normal);

    float diffuse = (dot > 0.0f) * dot;

    float3 reflect = -lightDir.Reflect(normal);

    float dot2 = reflect.DotProduct(viewDir);

    float specular = std::pow(dot2 * (dot2 > 0.0f), shiny);

    float epsilon = outAngle - inAngle;

    float angle = lightDir.DotProduct(dir.Normalize());

    float intensity = mathlib::saturate((outAngle - angle) / epsilon);

    float3 fragCol = (amb + diff * diffuse * intensity + spec * specular * intensity) * color;

    fragCol.saturate();

    return fragCol;
}
