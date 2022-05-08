#pragma once
#include "Light.h"
class SpotLight :
    public Light
{
private:
    float inAngle, outAngle;
    float3 dir;
public:
    SpotLight(float3 pos, float3 amb, float3 diff, float3 spec, float shiny, float3 dir, float inang, float outang)
        : Light(pos, amb, diff, spec, shiny), dir(dir) 
    {
        inAngle = std::cos(inang * 2 * M_PI / 360.0f);
        outAngle = std::cos(outang * 2 * M_PI / 360.0f);
    }
    float3 Calculate(Fragment* frag, VertexProcessor* vp) override;
};

