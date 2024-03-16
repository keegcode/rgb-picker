#include "include/window.h"

Window WindowCreate() {
  Window window = {.initalized=false, .width=1280, .height=960, .sdl=NULL, .renderer=NULL};
  
  int code = SDL_Init(SDL_INIT_EVERYTHING);
  if (code != 0) {
    fprintf(stderr, "Error initializing SDL2, code: %d", code);
    return window;
  };

  SDL_Window* sdlWindow = SDL_CreateWindow(
    "RGB Picker", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    window.width, 
    window.height, 
    SDL_WINDOW_BORDERLESS 
  );
  if (!sdlWindow) {
    fprintf(stderr, "Error initializing SDL2 window");
    return window;
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(sdlWindow, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Error initializing SDL2 renderer");
    return window;
  }
  
  window.sdl = sdlWindow;
  window.renderer = renderer;
  window.initalized = true;

  return window;
}

void WindowDestroy(Window *window) {
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->sdl);
  SDL_Quit();
}

