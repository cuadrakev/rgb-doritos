
//#include <stdio.h>
#include "Rasterizer.h"
#include "BMPUtility.h"

const int WIDTH = 256;
const int HEIGHT = 256;

IMAGE2D initImage()
{
    unsigned char*** image = new unsigned char** [WIDTH];
    for (int i = 0; i < WIDTH; i++)
    {
        image[i] = new unsigned char* [HEIGHT];
        for (int j = 0; j < HEIGHT; j++)
        {
            image[i][j] = new unsigned char[BYTES_PER_PIXEL];
        }
    }

    return image;
}

void deleteImage(IMAGE2D im)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            delete [] im[i][j];
        }
        delete [] im[i];
    }
    delete[] im;
}

int main()
{
    int color1 = 0xFF0000; //rgb
    int color2 = 0x00FF00; 
    int color3 = 0x0000FF; 

    IMAGE2D image = initImage();

    Point p1 = Point(-0.7f, -0.8f);
    Point p2 = Point(-1.4f, 0.5f);
    Point p3 = Point(0.0f, 0.9f); 

    Rasterizer* rasterizer = new Rasterizer(WIDTH, HEIGHT);

    rasterizer->drawTriangle(p1, color1, p2, color2, p3, color3, image);

    saveBMPFile(WIDTH, HEIGHT, image);

    printf("Finished");

    deleteImage(image);

    return 0;
}