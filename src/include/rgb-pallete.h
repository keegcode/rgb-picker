#pragma once

#include "window.h"

typedef struct {
  uint32_t base; 
  uint32_t selected;
  unsigned char step;
  SDL_Texture *texture;
} RGBPallete;

SDL_Texture* RGBPallete_CreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer, uint32_t *buffer); 
void RGBPallete_Decrement(RGBPallete *pallete);
void RGBPallete_Increment(RGBPallete *pallete);
void RGBPallete_Destroy(RGBPallete *pallete);

