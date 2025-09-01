#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdint.h>

struct BMPHeader {
  char signature[2];
  uint32_t filesize;
  uint32_t reserved;
  uint32_t dataoffset;
};

struct BMPInfoHeader {
  uint32_t size;
  uint32_t width;
  uint32_t heigth;
  uint16_t planes;
  uint16_t bitcount;
  uint32_t compression;
  uint32_t imagesize;
  uint32_t xppm;
  uint32_t yppm;
  uint32_t colorsimportant;
};

int main(int argc, char *argv[]) {
  std::cout << argv[1] << std::endl;
  std::ifstream file(argv[1], std::ios::binary);
  if (!file) {
    std::cout << "FileOpenError" << std::endl;
    return 1;
  }

  file.seekg(0, std::ios::beg);
  BMPHeader bmp;
  char bufferSing[2] = {};
  uint32_t bufferSize;
  uint32_t bufferReser;
  uint32_t bufferOffset;
  file.read(bufferSing, 2);
  bmp.signature[0] = bufferSing[0];
  bmp.signature[1] = bufferSing[1];
  file.read((char *)&bufferSize, 4);
  bmp.filesize = bufferSize;
  file.read((char *)&bufferReser, 4);
  bmp.reserved = bufferReser;
  file.read((char *)&bufferOffset, 4);
  bmp.dataoffset = bufferOffset;
  std::cout << "Signature: " << bmp.signature;
  std::cout << " " << " | Size in Byte of Signature: " << sizeof(bmp.signature);
  std::cout << std::endl;
  std::cout << "FileSize: " << bmp.filesize;
  std::cout << " " << " | Size in Byte of FileSize: " << sizeof(bmp.filesize);
  std::cout << std::endl;
  std::cout << "Reserved: " << bmp.reserved;
  std::cout << " " << " | Size in Byte of Reserved: " << sizeof(bmp.reserved);
  std::cout << std::endl;
  std::cout << "DataOffset: " << bmp.dataoffset;
  std::cout << " "
            << " | Size in Byte of DataOffset: " << sizeof(bmp.dataoffset);
  std::cout << std::endl;

  if (bmp.signature[0] == *"B" && bmp.signature[1] == *"M") {

    BMPInfoHeader bmpInfo;
    file.read((char *)&bmpInfo.size, 4);
    file.read((char *)&bmpInfo.heigth, 4);
    file.read((char *)&bmpInfo.width, 4);
    file.read((char *)&bmpInfo.planes, 2);
    file.read((char *)&bmpInfo.bitcount, 2);
    file.read((char *)&bmpInfo.compression, 4);
    file.read((char *)&bmpInfo.imagesize, 4);
    file.read((char *)&bmpInfo.xppm, 4);
    file.read((char *)&bmpInfo.yppm, 4);
    file.read((char *)&bmpInfo.colorsimportant, 4);

    std::cout << "Size: " << bmpInfo.size;
    std::cout << " " << " | Size in Byte of Size: " << sizeof(bmpInfo.size);
    std::cout << std::endl;
    std::cout << "Imagen heigth: " << bmpInfo.heigth;
    std::cout << " " << " | Size in Byte of heigth: " << sizeof(bmpInfo.heigth);
    std::cout << std::endl;
    std::cout << "Imagen width: " << bmpInfo.width;
    std::cout << " " << " | Size in Byte of width: " << sizeof(bmpInfo.width);
    std::cout << std::endl;
    std::cout << "Planeslanes: " << bmpInfo.planes;
    std::cout << " " << " | Size in Byte of Planes: " << sizeof(bmpInfo.planes);
    std::cout << std::endl;
    std::cout << "BitCount: " << bmpInfo.bitcount;
    std::cout << " "
              << " | Size in Byte of BitCount: " << sizeof(bmpInfo.bitcount);
    std::cout << std::endl;
    std::cout << "Compression: " << bmpInfo.compression;
    std::cout << " "
              << " | Size in Byte of Compression: "
              << sizeof(bmpInfo.compression);
    std::cout << std::endl;
    std::cout << "Image Size: " << bmpInfo.imagesize;
    std::cout << " "
              << " | Size in Byte of ImageSize: " << sizeof(bmpInfo.imagesize);
    std::cout << std::endl;
    std::cout << "X PixelPerM: " << bmpInfo.xppm;
    std::cout << " "
              << " | Size in Byte of X PixelPerM: " << sizeof(bmpInfo.xppm);
    std::cout << std::endl;
    std::cout << "Y PixelPerM: " << bmpInfo.yppm;
    std::cout << " "
              << " | Size in Byte of Y PixelPerM: " << sizeof(bmpInfo.yppm);
    std::cout << std::endl;
    std::cout << "ColorsImportant: " << bmpInfo.colorsimportant;
    std::cout << " "
              << " | Size in Byte of ColorsImportant: "
              << sizeof(bmpInfo.colorsimportant);
    std::cout << std::endl;
  }

  file.close();
  return 0;
}
