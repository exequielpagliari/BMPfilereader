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
  std::cout << " " << "Size in Byte of Signature: " << sizeof(bmp.signature);
  std::cout << std::endl;
  std::cout << "FileSize: " << bmp.filesize;
  std::cout << " " << "Size in Byte of FileSize: " << sizeof(bmp.filesize);
  std::cout << std::endl;
  std::cout << "Reserved: " << bmp.reserved;
  std::cout << " " << "Size in Byte of Reserved: " << sizeof(bmp.reserved);
  std::cout << std::endl;
  std::cout << "DataOffset: " << bmp.dataoffset;
  std::cout << " " << "Size in Byte of DataOffset: " << sizeof(bmp.dataoffset);
  std::cout << std::endl;

  file.close();
  return 0;
}
