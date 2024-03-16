#pragma once

#include "lib.h"

typedef struct {
  bool initalized;
  uint16_t width;
  uint16_t height;
  SDL_Window *sdl;
  SDL_Renderer *renderer;
} Window; 

Window WindowCreate();
void WindowDestroy(Window *window);
