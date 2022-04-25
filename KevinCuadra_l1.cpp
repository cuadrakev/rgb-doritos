
//#include <stdio.h>
#include "Rasterizer.h"
#include "BMPUtility.h"
#include "VertexProcessor.h"
#include <iostream>
#include <vector>
#include "SimpleTriangle.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Torus.h"

const int WIDTH = 640;
const int HEIGHT = 480;

int main()
{
    float3 UP(.0f, 1.0f, .0f);
    float3 cameraPos(.2f, -.3f, -1.0f);
    float3 centrePos(0, 0, 0);

    int color1 = 0xFF0000; //rgb
    int color2 = 0xFFFF00; 
    int color3 = 0x0000FF; 
    int color4 = 0x00FF00;

    int bgColor = 0x002020;

    VertexProcessor* vp = new VertexProcessor();
    Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT, BYTES_PER_PIXEL, vp);

    //vp->setPerspective(60, 4.0 / 3.0, 0.1, 100);
    vp->setLookat(cameraPos, centrePos, UP);

    rasterizer->clearBuffer(bgColor);

    //Cone* mesh1 = new Cone(0.5f, 0.7f, 10);
    Cylinder* mesh2 = new Cylinder(0.2f, 0.4f, 9, 3);
    Sphere* mesh3 = new Sphere(0.5f, 9, 12);
    Torus* mesh4 = new Torus(0.1f, 0.4f, 16, 6);

    //mesh1->makeNormals();
    mesh2->makeNormals();
    mesh3->makeNormals();
    mesh4->makeNormals();

    vp->resetTransform();
    vp->rotate(90, float3(0, 1, 0));
    //vp->translate(float3(0.6f, -0.5f, -0.3f));
    mesh3->draw(rasterizer, vp);

    //vp->resetTransform();
    ////vp->scale(float3(0.8f, 0.5f, 0.8f));
    ////vp->rotate(-60, float3(0, 1, 1));
    ////vp->translate(float3(-0.6f, -0.5f, -0.3f));
    //mesh2->draw(rasterizer, vp);

    //vp->resetTransform();
    ////vp->scale(float3(0.3f, 0.3f, 0.3f));
    ////vp->rotate(60, float3(1, 0, 0));
    ////vp->translate(float3(0.4f, -0.5f, 0));
    //mesh4->draw(rasterizer, vp);

    saveBMPFile(WIDTH, HEIGHT, rasterizer->colorBuffer);

    //delete mesh1;
    delete mesh2;
    delete mesh3;
    delete mesh4;
    delete rasterizer;
    delete vp;

    printf("Finished\n");

    return 0;
}