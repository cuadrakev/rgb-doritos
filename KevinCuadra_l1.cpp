
//#include <stdio.h>
#include <iostream>
#include <vector>

#include "Rasterizer.h"
#include "BMPUtility.h"
#include "VertexProcessor.h"

#include "SimpleTriangle.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Torus.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

const int WIDTH = 640;
const int HEIGHT = 480;

int main()
{
    float3 UP(.0f, -1.0f, .0f);
    float3 cameraPos(-.3f, -.6f, 1.5f);
    float3 centrePos(0, 0, 0);

    int bgColor = 0x101010;

    VertexProcessor* vp = new VertexProcessor();
    Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT, BYTES_PER_PIXEL, vp);

    vp->setPerspective(60, 4.0 / 3.0, -0.1, -100);
    vp->setLookat(cameraPos, centrePos, UP);

    DirectionalLight* d = new DirectionalLight(float3(0.5f, 0.2f, -0.0f), float3(0.0f, 0.0f, 0.1f), float3(0.8f, 0.8f, 0.8f), float3(0.5f, 0.3f, 0.3f), 32);
    //PointLight* p = new PointLight(float3(-0.5f, -.5f, -0.4f), float3(0.1f, 0.0f, 0.0f), float3(0.0f, 0.0f, 0.6f), float3(0.3f, 0.3f, 0.5f), 16);
    //SpotLight* s = new SpotLight(float3(-2.0f, -.0f, -2.0f), float3(0.0f, 0.05f, 0.0f), float3(0.0f, 0.4f, 0.0f), float3(0.1f, 0.f, 0.1f), 4, float3(1, 0, 1), 20, 30);

    rasterizer->lightsList.push_back(d);
    //rasterizer->lightsList.push_back(p);
    //rasterizer->lightsList.push_back(s);

    //Cone* mesh1 = new Cone(0.5f, 0.7f, 10);
    //Cylinder* mesh2 = new Cylinder(0.2f, 0.4f, 9, 3);
    Sphere* mesh3 = new Sphere(0.5f, 32, 18);
    Torus* mesh4 = new Torus(0.1f, 0.7f, 20, 10);

    //mesh1->makeNormals();
    //mesh2->makeNormals();
    mesh3->makeNormals();
    mesh4->makeNormals();

    rasterizer->clearBuffer(bgColor);

    vp->resetTransform();
    //vp->scale(float3(0.3f, 0.3f, 0.6f));
    //vp->rotate(60, float3(1, 0, 0));
    //vp->translate(float3(0.0f, 0.0f, -0.0f));
    vp->calcNormalMatrix();
    mesh4->setColor(0x909000);
    mesh4->draw(rasterizer, vp);

    vp->resetTransform();
    ////vp->scale(float3(0.8, 1.2, 1));
    ////vp->rotate(45, float3(1, 0, 0));
    //vp->translate(float3(-0.0f, -0.5f, -0.0f));
    vp->calcNormalMatrix();
    mesh3->setColor(0x0080FF);
    mesh3->draw(rasterizer, vp);

    //vp->resetTransform();
    //vp->scale(float3(0.8f, 0.5f, 0.8f));
    ////vp->rotate(-60, float3(0, 1, 1));
    //vp->translate(float3(-0.6f, -0.5f, -0.2f));
    //mesh2->drawGourard(rasterizer, vp);



    saveBMPFile(WIDTH, HEIGHT, rasterizer->colorBuffer);

    //delete mesh1;
    //delete mesh2;
    //delete mesh3;
    delete mesh4;
    delete rasterizer;
    delete d;
    //delete p;
    //delete s;
    delete vp;

    printf("Finished\n");

    return 0;
}