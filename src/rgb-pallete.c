#include "include/rgb-pallete.h"

RGBPallete RGBPallete_CreatePallete() {
  ColorBuffer buffer;
  RGBPallete pallete = {0xFFFF0000, 0xFFFF0000, 15};
  
  buffer.buffer = (uint32_t*) malloc(255 * 255 * sizeof(uint32_t));
  buffer.size = 255 * 255;

  pallete.buffer = buffer;

  return pallete;
}

SDL_Texture* RGBPallete_CreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer) {
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
  
  int height, width;
  int ul, ur, bl, br;

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
  
  for (int i = 0; i < height; i++) {
    double t = i / (double)(height - 1);
    int l = i * height + ul; 
    int r = i * height + ur; 
    buffer[l] = RGB_uint32_t_Lerp(buffer[ul], buffer[bl], t);
    buffer[r] = RGB_uint32_t_Lerp(buffer[ur], buffer[br], t);
  }
  
  for (int y = 0; y < height; y++) {
    int l = y * height;
    int r = (y * height) + width - 1;
    for (int x = 0; x < width; x++) {
      int i = y * height + x;
      double t = x / (double)ur;
      buffer[i] = RGB_uint32_t_Lerp(buffer[l], buffer[r], t);
    }
  }

  pallete->texture = texture;
  
  return pallete->texture;
}

void RGBPallete_Decrement(RGBPallete *pallete) {
  RGB rgb = RGB_from_uint32_t(pallete->base);

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
  
  pallete->base = RGB_to_uint32_t(&rgb);
}

void RGBPallete_Increment(RGBPallete *pallete) {
  RGB rgb = RGB_from_uint32_t(pallete->base);

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
  
  pallete->base = RGB_to_uint32_t(&rgb);
}

RGB RGBPallete_At(RGBPallete *pallete, int x, int y) {
  uint32_t color = pallete->buffer.buffer[y * 255 + x];
  return RGB_from_uint32_t(color);
}

void RGBPallete_Destroy(RGBPallete *pallete) {
  free(pallete->buffer.buffer);
  SDL_DestroyTexture(pallete->texture);
}

