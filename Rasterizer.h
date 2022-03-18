#pragma once

typedef unsigned char*** IMAGE2D;

struct Point {
    float x, y;

    Point(float x, float y) : x(x), y(y) {}
};

class Rasterizer
{
public:

    Rasterizer(int w, int h)
    {
        WIDTH = w;
        HEIGHT = h;
    }

	void drawTriangle(Point p1, int c1, Point p2, int c2, Point p3, int c3, IMAGE2D image);

private:

    int WIDTH, HEIGHT;

	void trimTriangle(int& minx, int& miny, int& maxx, int& maxy, Point p1, Point p2, Point p3);

    void defineDiffs(float& dx12, float& dx23, float& dx31, float& dy12, float& dy23, float& dy31, Point p1, Point p2, Point p3);

    void colorToComponents(unsigned char& r, unsigned char& g, unsigned char& b, int color);

    int convertToRender(float pos, int dim);

    float convertToCanon(float pos, int dim);

    bool halfPlaneCheck(float dx, float dy, float cx, float cy);

    bool triangleCheck(float dx12, float dx23, float dx31, float dy12, float dy23, float dy31,
        float cx1, float cx2, float cx3, float cy1, float cy2, float cy3);

    bool triangleCheckInv(float dx12, float dx23, float dx31, float dy12, float dy23, float dy31,
        float cx1, float cx2, float cx3, float cy1, float cy2, float cy3);
};

