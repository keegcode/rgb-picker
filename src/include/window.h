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

Window Window_Create();
void Window_Destroy(Window *window);
