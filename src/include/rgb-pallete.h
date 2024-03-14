#pragma once

#include "window.h"
#include "rgb.h"

typedef struct {
  uint32_t *buffer;
  size_t size;
} ColorBuffer;

typedef struct {
  uint32_t base; 
  uint32_t selected;
  unsigned char step;
  ColorBuffer buffer;
  SDL_Texture *texture;
} RGBPallete;

RGBPallete RGBPallete_CreatePallete();
SDL_Texture* RGBPallete_CreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer); 
RGB RGBPallete_At(RGBPallete *pallete, int x, int y);
void RGBPallete_Decrement(RGBPallete *pallete);
void RGBPallete_Increment(RGBPallete *pallete);
void RGBPallete_Destroy(RGBPallete *pallete);

