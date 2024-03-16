#pragma once

#include "window.h"
#include "rgb.h"

typedef struct {
  uint32_t *buffer;
  size_t size;
} ColorBuffer;

typedef struct {
  uint32_t base; 
  uint8_t step;
  ColorBuffer buffer;
  SDL_Texture *texture;
} RGBPallete;

RGBPallete RGBPalleteCreate();
SDL_Texture* RGBPalleteCreateSDLTexture(RGBPallete *pallete, SDL_Renderer *renderer); 
RGB RGBPalleteAt(RGBPallete *pallete, uint8_t x, uint8_t y);
void RGBPalleteDecrement(RGBPallete *pallete);
void RGBPalleteIncrement(RGBPallete *pallete);
void RGBPalleteDestroy(RGBPallete *pallete);

