
//#include <stdio.h>
#include "Rasterizer.h"
#include "BMPUtility.h"

const int WIDTH = 640;
const int HEIGHT = 480;



int main()
{
    int color1 = 0xFF0000; //rgb
    int color2 = 0xFFFF00; 
    int color3 = 0x0000FF; 
    int color4 = 0x00FF00;

    int bgColor = 0xB0B0B0;

    // Triangle 1
    Point p1 = Point(-0.7f, -0.8f);
    Point p2 = Point(-0.5f, 0.4f);
    Point p3 = Point(-0.8f, 0.9f); 

    // Triangle 2
    //Point p4 = Point(-0.7f, -0.8f);
    //Point p5 = Point(-0.5f, 0.6f);
    Point p4 = Point(0.8f, -0.2f);

    // Triagnle 3
    Point p5 = Point(-0.2f, -0.9f, 0.2f);
    Point p6 = Point(0.0f, 0.9f, -0.2f);
    Point p7 = Point(0.2f, -0.8f, 0.2f);

    Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT, BYTES_PER_PIXEL);

    rasterizer->clearBuffer(bgColor);
    rasterizer->drawTriangle(p1, p3, p2, color1, color3, color2);
    rasterizer->drawTriangle(p1, p2, p4, color1, color2, color4);
    rasterizer->drawTriangle(p5, p6, p7, color3);

    saveBMPFile(WIDTH, HEIGHT, rasterizer->colorBuffer);

    printf("Finished");

    delete rasterizer;

    return 0;
}