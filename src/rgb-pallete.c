#include "include/rgb-pallete.h"

SDL_Texture* RGBPallete_CreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer, uint32_t *buffer) {
  SDL_Texture *texture = SDL_CreateTexture(
    renderer, 
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STREAMING, 
    255, 
    255 
  );
  
  int height, width;
  int ul, ur, bl, br;

  height = 255;
  width = 255;
  
  ul = 0;
  ur = width - 1;
  bl = height * (height - 1);
  br = bl + ur;
  
  buffer[ul] = 0xFFFFFFFF;
  buffer[ur] = pallete->base;
  buffer[bl] = 0xFF000000;
  buffer[br] = 0xFF000000;
  
  for (int i = 0; i < height; i++) {
    double t = i / (double)(height - 1);
    int l = i * height + ul; 
    int r = i * height + ur; 
    buffer[l] = lerpRGB(buffer[ul], buffer[bl], t);
    buffer[r] = lerpRGB(buffer[ur], buffer[br], t);
  }
  
  for (int y = 0; y < height; y++) {
    int l = y * height;
    int r = (y * height) + width - 1;
    for (int x = 0; x < width; x++) {
      int i = y * height + x;
      double t = x / (double)ur;
      buffer[i] = lerpRGB(buffer[l], buffer[r], t);
    }
  }
  
  return texture;
}

void RGBPallete_Decrement(RGBPallete *pallete) {
  uint32_t color = pallete->base;
  char step = pallete->step;

  unsigned char r = (color >> 16) & 0xFF;
  unsigned char g = (color >> 8) & 0xFF;
  unsigned char b = color & 0xFF;

  if (r == 255 && b == 0) {
    g += step;
  }
  
  if (r == 255 && b > 0) {
    b -= step;
  }

  if (g == 255 && r > 0) {
    r -= step;
  }

  if (g == 255 && r == 0) {
    b += step;
  }
  
  if (b == 255 && g > 0) {
    g -= step;
  }
  
  if (b == 255 && g == 0) {
    r += step;
  }
  
  pallete->base = 0xFF000000 | (r << 16) | (g << 8) | b;
}

void RGBPallete_Increment(RGBPallete *pallete) {
  uint32_t color = pallete->base;
  char step = pallete->step;

  unsigned char r = (color >> 16) & 0xFF;
  unsigned char g = (color >> 8) & 0xFF;
  unsigned char b = color & 0xFF;

  if (r == 255 && g == 0) {
    b += step;
  }
  
  if (r == 255 && g > 0) {
    g -= step;
  }

  if (g == 255 && b > 0) {
    b -= step;
  }

  if (g == 255 && b == 0) {
    r += step;
  }
  
  if (b == 255 && r > 0) {
    r -= step;
  }
  
  if (b == 255 && r == 0) {
    g += step;
  }
  
  pallete->base = 0xFF000000 | (r << 16) | (g << 8) | b;
}

uint32_t lerpRGB(uint32_t color1, uint32_t color2, double t) {
  unsigned char r1 = (color1 >> 16) & 0xFF;
  unsigned char g1 = (color1 >> 8) & 0xFF;
  unsigned char b1 = color1 & 0xFF;

  unsigned char r2 = (color2 >> 16) & 0xFF;
  unsigned char g2 = (color2 >> 8) & 0xFF;
  unsigned char b2 = color2 & 0xFF;

  unsigned char r = (unsigned char)(r1 + (r2 - r1) * t);
  unsigned char g = (unsigned char)(g1 + (g2 - g1) * t);
  unsigned char b = (unsigned char)(b1 + (b2 - b1) * t);

  return 0xFF000000 | (r << 16) | (g << 8) | b;
}
