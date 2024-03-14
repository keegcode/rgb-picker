#include "include/loop.h"

LoopState Loop_Setup() {
  Window window = Window_Create();
  RGBPallete pallete = RGBPallete_CreatePallete();  
  return (LoopState){window, pallete, window.initalized};
}

void Loop_ProcessInput(LoopState *state) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          state->isRunning = false;
          break;
        case SDL_WINDOWEVENT:
          processWindowEvent(&event.window, state);
          break;
        case SDL_KEYDOWN:
          processKeyDownEvent(&event.key, state);
          break;
        case SDL_MOUSEBUTTONUP: 
          processMouseButtonUpEvent(&event.button, state);
          break;
        default:
          break;
      }
    }
}

void Loop_Render(LoopState *state) {
  SDL_Renderer *renderer = state->window.renderer;
  SDL_Texture *texture = RGBPallete_CreateSDLTexture(&state->pallete, renderer);

  SDL_UpdateTexture(texture, NULL, state->pallete.buffer.buffer, 255 * (sizeof(uint32_t)));
  
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void Loop_Destroy(LoopState *state) {
  RGBPallete_Destroy(&state->pallete);
  Window_Destroy(&state->window);
}

void processWindowEvent(SDL_WindowEvent *event, LoopState* state) {
  switch (event->event) {
    case SDL_WINDOWEVENT_CLOSE:
      state->isRunning = false;
      break;
    default:
      break;
  }
}

void processKeyDownEvent(SDL_KeyboardEvent *event, LoopState* state) {
  switch (event->keysym.sym) {
    case SDLK_ESCAPE:
      state->isRunning = false;
      break;
    case SDLK_DOWN:
      RGBPallete_Decrement(&state->pallete);
      break;
    case SDLK_UP:
      RGBPallete_Increment(&state->pallete);
      break;
    default:
      break;
  }
}

void processMouseButtonUpEvent(SDL_MouseButtonEvent *event, LoopState* state) {
  int x, y;
  
  x = (((double) event->x / (double) state->window.width)) * 255;
  y = (((double) event->y / (double) state->window.height)) * 255;

  RGB color = RGBPallete_At(&state->pallete, x, y);
  switch (event->button) {
    case SDL_BUTTON_LEFT:
      printf("RGB: [%d, %d, %d]\n", color.r, color.g, color.b);
      break;
    default:
      break;
  }
}
