#pragma once

#include "lib.h"

typedef struct {
  uint32_t *buffer;
  size_t size;
} ColorBuffer;

typedef struct {
  bool initalized;
  int width;
  int height;
  
  ColorBuffer colorBuffer;

  SDL_Window *window;
  SDL_Renderer *renderer;
} Window; 

Window createWindow();
void destroyWindow(Window *window);
