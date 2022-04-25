#include "Rasterizer.h"
#include <algorithm>

void Rasterizer::clearBuffer(int color)
{
    unsigned char r, g, b;

    colorToComponents(r, g, b, color);

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            colorBuffer[i][j][0] = b;
            colorBuffer[i][j][1] = g;
            colorBuffer[i][j][2] = r;
            colorBuffer[i][j][3] = 0xFF;
            depthBuffer[i][j][0] = 0xFF;
        }
    }
}

void Rasterizer::drawTriangle(float3 p1, float3 p2, float3 p3, int c)
{
    drawTriangle(p1, p2, p3, c, c, c);
}

void Rasterizer::drawTriangle(float3 p1, float3 p2, float3 p3, int c1, int c2, int c3)
{
    //transform points
    p1 = vp->getObj2Proj() * p1;
    p2 = vp->getObj2Proj() * p2;
    p3 = vp->getObj2Proj() * p3;
    
    unsigned char r1, r2, r3, g1, g2, g3, b1, b2, b3;
    colorToComponents(r1, g1, b1, c1);
    colorToComponents(r2, g2, b2, c2);
    colorToComponents(r3, g3, b3, c3);

    int minx, miny, maxx, maxy;

    trimTriangle(minx, miny, maxx, maxy, p1, p2, p3);

    float dx12, dx23, dx31, dy12, dy23, dy31;

    float* diffs[6] = { &dx12, &dx23, &dx31, &dy12, &dy23, &dy31 };

    defineDiffs(dx12, dx23, dx31, dy12, dy23, dy31, p1, p2, p3);

    bool lt1 = false, lt2 = false, lt3 = false;

    lt1 = checkLeftTop(dx12, dy12);
    lt2 = checkLeftTop(dx23, dy23);
    lt3 = checkLeftTop(dx31, dy31);

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (i >= minx && i <= maxx && j >= miny && j <= maxy)
            {
                float i_canon = convertToCanon((float)i, WIDTH);
                float j_canon = convertToCanon((float)j, HEIGHT);

                float cx1 = i_canon - p1.x;
                float cy1 = j_canon - p1.y;
                float cx2 = i_canon - p2.x;
                float cy2 = j_canon - p2.y;
                float cx3 = i_canon - p3.x;
                float cy3 = j_canon - p3.y;

                if (triangleCheck(dx12, dx23, dx31, dy12, dy23, dy31, cx1, cx2, cx3, cy1, cy2, cy3, lt1, lt2, lt3))
                {
                    float lambda1 = ((dy23 * cx3) + ((-dx23) * cy3)) / 
                                     ((dy23 * (-dx31)) + ((-dx23) * (-dy31)));
                    float lambda2 = ((dy31 * cx3) + ((-dx31) * cy3)) / 
                                     ((dy31 * dx23) + ((-dx31) * dy23));

                    float lambda3 = (1 - lambda1 - lambda2);

                    unsigned char B = lambda1 * b1 + lambda2 * b2 + lambda3 * b3;
                    unsigned char G = lambda1 * g1 + lambda2 * g2 + lambda3 * g3;
                    unsigned char R = lambda1 * r1 + lambda2 * r2 + lambda3 * r3;

                    float depth = lambda1 * p1.z + lambda2 * p2.z + lambda3 * p3.z;

                    depth = convertToRender(depth, 255);

                    if (depth < depthBuffer[i][j][0])
                    {
                        colorBuffer[i][j][0] = B;
                        colorBuffer[i][j][1] = G;
                        colorBuffer[i][j][2] = R;
                        /*colorBuffer[i][j][0] = depth;
                        colorBuffer[i][j][1] = depth;
                        colorBuffer[i][j][2] = depth;*/
                        colorBuffer[i][j][3] = 0xFF;
                        depthBuffer[i][j][0] = depth;
                    }
                }
                //else if (triangleCheckInv(dx12, dx23, dx31, dy12, dy23, dy31, cx1, cx2, cx3, cy1, cy2, cy3)) 
                //{
                //    colorBuffer[i][j][0] = 0xFF;
                //    colorBuffer[i][j][1] = 0x00;
                //    colorBuffer[i][j][2] = 0xFF;
                //    colorBuffer[i][j][3] = 0xFF;
                //}
            }
        }
    }
}

void Rasterizer::drawTriangle(float3 p1, float3 p2, float3 p3, float3 c1, float3 c2, float3 c3)
{
    int color1 = vectorToColors(c1);
    int color2 = vectorToColors(c2);
    int color3 = vectorToColors(c3);
    drawTriangle(p1, p2, p3, color1, color2, color3);
}

void Rasterizer::trimTriangle(int& minx, int& miny, int& maxx, int& maxy, float3 p1, float3 p2, float3 p3)
{
    // defining the search rectangle
    minx = convertToRender(std::min({ p1.x, p2.x, p3.x }), WIDTH);
    miny = convertToRender(std::min({ p1.y, p2.y, p3.y }), HEIGHT);
    maxx = convertToRender(std::max({ p1.x, p2.x, p3.x }), WIDTH);
    maxy = convertToRender(std::max({ p1.y, p2.y, p3.y }), HEIGHT);

    // trimming the triangle to screens
    minx = std::max(minx, 0);
    miny = std::max(miny, 0);
    maxx = std::min(maxx, WIDTH - 1);
    maxy = std::min(maxy, HEIGHT - 1);
}

void Rasterizer::defineDiffs(float& dx12, float& dx23, float& dx31, float& dy12, float& dy23, float& dy31, float3 p1, float3 p2, float3 p3)
{
    dx12 = p1.x - p2.x;
    dx23 = p2.x - p3.x;
    dx31 = p3.x - p1.x;
    dy12 = p1.y - p2.y;
    dy23 = p2.y - p3.y;
    dy31 = p3.y - p1.y;
}

void Rasterizer::colorToComponents(unsigned char& r, unsigned char& g, unsigned char& b, int color)
{
    r = (color & 0xFF0000) >> 16;
    g = (color & 0x00FF00) >> 8;
    b = color & 0x0000FF;
}

int Rasterizer::vectorToColors(float3 vec)
{
    int red = 0xFF0000 * vec.r;
    int green = 0xFF00 * vec.g;
    int blue = 0xFF * vec.b;

    return (red & 0xFF0000) + (green & 0xFF00) + blue;
}

int Rasterizer::convertToRender(float pos, int dim)
{
    return (pos + 1) * 0.5f * dim;
}

float Rasterizer::convertToCanon(float pos, int dim)
{
    return 2 * pos / dim - 1;
}

bool Rasterizer::halfPlaneCheck(float dx, float dy, float cx, float cy, bool lt)
{
    if ((!lt && dx * cy - dy * cx > 0) || (lt && dx * cy - dy * cx >= 0))
        return true;
    return false;
}

bool Rasterizer::triangleCheck(float dx12, float dx23, float dx31, float dy12, float dy23, float dy31,
    float cx1, float cx2, float cx3, float cy1, float cy2, float cy3,
    bool lt1, bool lt2, bool lt3)
{
    return halfPlaneCheck(dx12, dy12, cx1, cy1, lt1) && halfPlaneCheck(dx23, dy23, cx2, cy2, lt2) && halfPlaneCheck(dx31, dy31, cx3, cy3, lt3);
}

bool Rasterizer::triangleCheckInv(float dx12, float dx23, float dx31, float dy12, float dy23, float dy31,
    float cx1, float cx2, float cx3, float cy1, float cy2, float cy3)
{
    return !halfPlaneCheck(dx12, dy12, cx1, cy1, false) && !halfPlaneCheck(dx23, dy23, cx2, cy2, false) && !halfPlaneCheck(dx31, dy31, cx3, cy3, false);
}

bool Rasterizer::checkLeftTop(const float& dx, const float& dy)
{
    return (dy < 0 || (dy == 0 && dx > 0));
}

IMAGE2D Rasterizer::initImage(int b)
{
    IMAGE2D im = new unsigned char** [WIDTH];
    for (int i = 0; i < WIDTH; i++)
    {
        im[i] = new unsigned char* [HEIGHT];
        for (int j = 0; j < HEIGHT; j++)
        {
            im[i][j] = new unsigned char[b];
        }
    }

    return im;
}

void Rasterizer::deleteImage(IMAGE2D im)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            delete[] im[i][j];
        }
        delete[] im[i];
    }
    delete[] im;
}
