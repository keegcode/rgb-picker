#include "include/rgb-pallete.h"

RGBPallete RGBPalleteCreate() {
  ColorBuffer buffer = {.buffer=NULL, .size=(255 * 255)};
  RGBPallete pallete = {.base=0xFFFF0000, .buffer=buffer, .step=15, .texture=NULL};
  
  pallete.buffer.buffer = (uint32_t*) malloc(255 * 255 * sizeof(uint32_t));

  return pallete;
}

SDL_Texture* RGBPalleteCreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer) {
  SDL_Texture *texture = pallete->texture;

  if (texture == NULL) {
    texture = SDL_CreateTexture(
      renderer, 
      SDL_PIXELFORMAT_ARGB8888, 
      SDL_TEXTUREACCESS_STREAMING, 
      255, 
      255 
    );
  } 
  
  uint8_t height, width;
  size_t ul, ur, bl, br;

  height = 255;
  width = 255;
  
  ul = 0;
  ur = width - 1;
  bl = height * (height - 1);
  br = bl + ur;

  uint32_t *buffer = pallete->buffer.buffer;
  
  buffer[ul] = 0xFFFFFFFF;
  buffer[ur] = pallete->base;
  buffer[bl] = 0xFF000000;
  buffer[br] = 0xFF000000;
  
  for (size_t i = 0; i < height; i++) {
    double t = i / (double)(height - 1);
    size_t l = i * height + ul; 
    size_t r = i * height + ur; 
    buffer[l] = RGBU32Lerp(buffer[ul], buffer[bl], t);
    buffer[r] = RGBU32Lerp(buffer[ur], buffer[br], t);
  }
  
  for (size_t y = 0; y < height; y++) {
    size_t l = y * height;
    size_t r = (y * height) + width - 1;
    for (size_t x = 0; x < width; x++) {
      size_t i = y * height + x;
      double t = x / (double)ur;
      buffer[i] = RGBU32Lerp(buffer[l], buffer[r], t);
    }
  }

  pallete->texture = texture;
  
  return pallete->texture;
}

void RGBPalleteDecrement(RGBPallete *pallete) {
  RGB rgb = RGBFromU32(pallete->base);

  if (rgb.r == 255 && rgb.b == 0) {
    rgb.g += pallete->step;
  }
  
  if (rgb.r == 255 && rgb.b > 0) {
    rgb.b -= pallete->step;
  }

  if (rgb.g == 255 && rgb.r > 0) {
    rgb.r -= pallete->step;
  }

  if (rgb.g == 255 && rgb.r == 0) {
    rgb.b += pallete->step;
  }
  
  if (rgb.b == 255 && rgb.g > 0) {
    rgb.g -= pallete->step;
  }
  
  if (rgb.b == 255 && rgb.g == 0) {
    rgb.r += pallete->step;
  }
  
  pallete->base = RGBToU32(&rgb);
}

void RGBPalleteIncrement(RGBPallete *pallete) {
  RGB rgb = RGBFromU32(pallete->base);

  if (rgb.r == 255 && rgb.g == 0) {
    rgb.b += pallete->step;
  }
  
  if (rgb.r == 255 && rgb.g > 0) {
    rgb.g -= pallete->step;
  }

  if (rgb.g == 255 && rgb.b > 0) {
    rgb.b -= pallete->step;
  }

  if (rgb.g == 255 && rgb.b == 0) {
    rgb.r += pallete->step;
  }
  
  if (rgb.b == 255 && rgb.r > 0) {
    rgb.r -= pallete->step;
  }
  
  if (rgb.b == 255 && rgb.r == 0) {
    rgb.g += pallete->step;
  }
  
  pallete->base = RGBToU32(&rgb);
}

RGB RGBPalleteAt(RGBPallete *pallete, uint8_t x, uint8_t y) {
  uint32_t color = pallete->buffer.buffer[y * 255 + x];
  return RGBFromU32(color);
}

void RGBPalleteDestroy(RGBPallete *pallete) {
  free(pallete->buffer.buffer);
  SDL_DestroyTexture(pallete->texture);
}

