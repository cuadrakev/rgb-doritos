#pragma once
#include "Mesh.h"
class Sphere :
    public Mesh
{
public:
    Sphere(float radius, int sides, int levels);
};

