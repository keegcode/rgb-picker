#include "include/window.h"

Window Window_Create() {
  ColorBuffer buffer = {NULL, 0};
  Window result = {false, 0, 0, buffer, NULL, NULL};
  
  int code = SDL_Init(SDL_INIT_EVERYTHING);
  if (code != 0) {
    fprintf(stderr, "Error initializing SDL2, code: %d", code);
    return result;
  };

  int w, h;
  w = 1280;
  h = 960;

  SDL_Window* window = SDL_CreateWindow(
    "RGB Picker", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    w, 
    h, 
    SDL_WINDOW_RESIZABLE 
  );
  if (!window) {
    fprintf(stderr, "Error initializing SDL2 window");
    return result;
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Error initializing SDL2 renderer");
    return result;
  }
  
  result.window = window;
  result.renderer = renderer;
  result.initalized = true;
  result.colorBuffer.buffer = (uint32_t*) malloc(w * h * sizeof(uint32_t));
  result.colorBuffer.size = w * h;
  result.width = w;
  result.height = h;

  return result;
}

uint32_t Window_GetColorAt(Window *window, int x, int y) {
  return window->colorBuffer.buffer[y * window->height + x]; 
}

void Window_Destroy(Window *window) {
  free(window->colorBuffer.buffer);
  
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);
  SDL_Quit();
}

