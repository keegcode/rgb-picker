#pragma once

#include "window.h"

typedef struct {
  uint32_t base; 
  uint32_t selected;
} RGBPallete;

SDL_Texture* RGBPallete_CreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer, uint32_t *buffer); 
uint32_t lerpRGB(uint32_t color1, uint32_t color2, double t);
