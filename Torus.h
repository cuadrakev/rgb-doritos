#pragma once
#include "Mesh.h"
class Torus :
    public Mesh
{
public:
    Torus(float innerRad, float outerRad, int poloidSegments, int toroidSegments);
};

