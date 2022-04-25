#include "DirectionalLight.h"
#include <cmath>

float3 DirectionalLight::Calculate(Fragment* frag, VertexProcessor* vp)
{
    float3x3 normalMat = vp->getNormalMatrix();

    float3x3 worldMat = vp->obj2world.subMatrix(3,3);

    float3 color = float3(1, 1, 1);

    float3 lightDir = (-pos).Normalize();

    float3 normal = (normalMat * frag->normal).Normalize();

    //float3 reflect = -lightDir.Reflect(normal);

    float dot = lightDir.DotProduct(normal);

    float diffuse = dot * (dot > 0.0f);

    //float dot2 = reflect.DotProduct(lightDir);

    float specular = 0;// std::pow(dot2 * (dot2 > 0.0f), shiny);

    float3 fragCol = (amb + diff * diffuse + spec * specular) * color;

    fragCol.saturate();

    return fragCol;
}
