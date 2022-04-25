#pragma once
#include "float3.h"
#include "VertexProcessor.h"

typedef unsigned char*** IMAGE2D;

//struct Point {
//    float x, y, z;
//
//    Point(float x, float y, float z = 0) : x(x), y(y) , z(z) {}
//};

class Rasterizer
{
public:

    Rasterizer(int w, int h, int b, VertexProcessor* vp)
    {
        WIDTH = w;
        HEIGHT = h;
        colorBuffer = initImage(b);
        depthBuffer = initImage(1);
        this->vp = vp;
    }

    ~Rasterizer()
    {
        deleteImage(colorBuffer);
        deleteImage(depthBuffer);
    }

	void drawTriangle(float3 p1, float3 p2, float3 p3, int c1, int c2, int c3);

	void drawTriangle(float3 p1, float3 p2, float3 p3, float3 c1, float3 c2, float3 c3);

    void clearBuffer(int color);

	void drawTriangle(float3 p1, float3 p2, float3 p3, int c);

    IMAGE2D colorBuffer;

private:

    int WIDTH, HEIGHT;

    IMAGE2D depthBuffer;

    VertexProcessor* vp;

	void trimTriangle(int& minx, int& miny, int& maxx, int& maxy, float3 p1, float3 p2, float3 p3);

    void defineDiffs(float& dx12, float& dx23, float& dx31, float& dy12, float& dy23, float& dy31, float3 p1, float3 p2, float3 p3);

    void colorToComponents(unsigned char& r, unsigned char& g, unsigned char& b, int color);

    int vectorToColors(float3 vec);

    int convertToRender(float pos, int dim);

    float convertToCanon(float pos, int dim);

    bool halfPlaneCheck(float dx, float dy, float cx, float cy, bool lt);

    bool triangleCheck(float dx12, float dx23, float dx31, float dy12, float dy23, float dy31,
        float cx1, float cx2, float cx3, float cy1, float cy2, float cy3,
        bool lt1, bool lt2, bool lt3);

    bool triangleCheckInv(float dx12, float dx23, float dx31, float dy12, float dy23, float dy31,
        float cx1, float cx2, float cx3, float cy1, float cy2, float cy3);

    bool checkLeftTop(const float& dx, const float& dy);

    IMAGE2D initImage(int b);

    void deleteImage(IMAGE2D im);
};

