
//#include <stdio.h>
#include "Rasterizer.h"
#include "BMPUtility.h"
#include "VertexProcessor.h"
#include <iostream>
#include <vector>

const int WIDTH = 640;
const int HEIGHT = 480;

int main()
{
    float3 UP(.0f, 1.0f, .0f);
    float3 cameraPos(.0f, 0.0f, -2.0f);
    float3 centrePos(0, 0, 0);

    int color1 = 0xFF0000; //rgb
    int color2 = 0xFFFF00; 
    int color3 = 0x0000FF; 
    int color4 = 0x00FF00;

    int bgColor = 0x000000;

    // Triangle 1
    float3 p1(-0.1f, -0.6f, -0.5f);
    float3 p2(-0.5f, -0.1f, -0.5f);
    float3 p3(-0.8f, -0.6f, -0.5f);

    //// Triangle 2
    //float3 p4(0.5f, -0.6f, -0.7f);
    //float3 p5(0.1f, -0.1f, -0.7f);
    //float3 p6(0.1f, 0.6f, -0.7f);

    //// Triangle 2
    ////Point p4 = Point(-0.7f, -0.8f);
    ////Point p5 = Point(-0.5f, 0.6f);
    float3 p4(0.8f, 0.5f, -0.5f);

    // Triagnle 3
    float3 p5(-0.2f, -0.9f, -0.1f);
    float3 p6(0.0f, 0.9f, -0.9f);
    float3 p7(0.2f, -0.8f, -0.1f);

    float3 p8(-0.5f, 0.5f, 0.f);
    float3 p9(-0.0f, -0.5f, 0.f);
    float3 p10(0.5f, 0.5f, 0.f);

    VertexProcessor* vp = new VertexProcessor();

    //vp->setPerspective(60, 4.0 / 3.0, 0.1, 100);
    //vp->setLookat(cameraPos, centrePos, UP);

    Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT, BYTES_PER_PIXEL, vp);

    rasterizer->clearBuffer(bgColor);
    rasterizer->drawTriangle(p5, p6, p7, color3);

    //vp->rotate(90, float3(0, 0, 1));
    rasterizer->drawTriangle(p1, p2, p4, color1, color3, color2);
    
    vp->resetTransform();
    
    vp->scale(float3(2, 1, 1));
    vp->rotate(-90, float3(0,0,1));
    vp->translate(float3(-0.3, 0, -0.6));
    

    rasterizer->drawTriangle(p8, p10, p9, color1, color4, color3);

    saveBMPFile(WIDTH, HEIGHT, rasterizer->colorBuffer);

    printf("Finished\n");

    delete rasterizer;

    return 0;
}