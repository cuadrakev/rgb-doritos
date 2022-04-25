#pragma once
#include "Mesh.h"
class Cylinder :
    public Mesh
{
public:
    Cylinder(float radius, float height, int sides, int levels);
};

