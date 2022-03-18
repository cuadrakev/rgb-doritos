#pragma once

#include <fstream>
#include <iostream>

typedef unsigned char*** IMAGE2D;

const int BYTES_PER_PIXEL = 4;
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void saveBMPFile(const int& width, const int& height, IMAGE2D image)
{
    std::ofstream imageFile;

    imageFile.open("generatedImage.bmp");

    //int padSize = (4 - (width * 3) % 4) % 4;
    int sizeData = width * height * BYTES_PER_PIXEL;// +height * padSize;

    //createFileHeader
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + sizeData;

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    imageFile.write((char*)fileHeader, 14);

    //createInfoHeader
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

    imageFile.write((char*)infoHeader, 40);

    //unsigned char padding[3] = { padSize,padSize,padSize };

    //writing file
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            //if(height - 30 <= j && j <= height-10)
            //    std::cout << (int)image[i][j][0] << " " << (int)image[i][j][1] << " " << (int)image[i][j][2] << " " << (int)image[i][j][3] << '\n';
            imageFile.write((const char*)image[i][j], 4);
        }
        //imageFile.write((char*)padding, padSize);
    }

    imageFile.close();
}
