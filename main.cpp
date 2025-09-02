#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>

#include <SDL2/SDL.h>
#include <stdio.h>

// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

SDL_Surface *imageNew = NULL;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia(const char *argument);

// Frees media and shuts down SDL
void close();

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

struct Image {

  uint8_t *rgb_data;
  int width;
  int heigth;
  int depth;
  int pitch;
};

Image *img;

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
    std::cout << "Acá Llega";
    int bytesPerPixel = bmpInfo.bitcount / 8; // ej. 24 bits → 3
    int rowSize = ((bmpInfo.width * bytesPerPixel + 3) / 4) * 4;
    int imageSize = rowSize * bmpInfo.heigth;
    std::cout << "Acá Llega";
    std::vector<unsigned char> raw(imageSize);
    int pitch =
        ((bmpInfo.heigth * bytesPerPixel + 3) / 4) * 4; // stride con padding
    std::cout << "Acá Llega";
    file.seekg(bmp.dataoffset, std::ios::beg);
    file.read((char *)raw.data(), imageSize);

    img->rgb_data = raw.data();
    img->width = bmpInfo.width;
    img->heigth = bmpInfo.heigth;
    img->depth = bmpInfo.bitcount;
    img->pitch = pitch;

    SCREEN_HEIGHT = bmpInfo.heigth;
    SCREEN_WIDTH = bmpInfo.width;
  }

  file.close();

  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    if (!loadMedia(argv[1])) {
      printf("Failed to load media!\n");
    } else {

      // Apply the image
      // SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
      SDL_BlitSurface(imageNew, NULL, gScreenSurface, NULL);
      // Update the surface
      SDL_UpdateWindowSurface(gWindow);
      // Hack to get window to stay up
      SDL_Event e;
      bool quit = false;
      while (quit == false) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT)
            quit = true;
        }
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia(const char *argument) {
  // Loading success flag
  bool success = true;

  imageNew = SDL_CreateRGBSurfaceFrom(img->rgb_data, img->width, img->heigth,
                                      img->depth, img->pitch, 0x0000FF,
                                      0x00FF00, 0xFF0000, 0);
  if (imageNew == NULL) {
    printf("Unable to load image ! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  // Load splash image
  gHelloWorld = SDL_LoadBMP(argument);
  if (gHelloWorld == NULL) {
    printf("Unable to load image ! SDL Error: %s\n", SDL_GetError());
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surface
  SDL_FreeSurface(gHelloWorld);
  SDL_FreeSurface(imageNew);
  gHelloWorld = NULL;
  imageNew = NULL;
  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}
