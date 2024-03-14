#pragma once

#include "lib.h"

typedef struct {
  bool initalized;
  int width;
  int height;
  SDL_Window *window;
  SDL_Renderer *renderer;
} Window; 

Window Window_Create();
void Window_Destroy(Window *window);
