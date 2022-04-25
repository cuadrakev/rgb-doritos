#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
public:
    DirectionalLight(float3 pos, float3 amb, float3 diff, float3 spec, float shiny) 
        : Light(pos, amb, diff, spec, shiny) {}
    float3 Calculate(Fragment* frag, VertexProcessor* vp) override;
};

