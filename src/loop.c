#include "include/loop.h"

LoopState LoopSetup() {
  Window window = WindowCreate();
  RGBPallete pallete = RGBPalleteCreate();  
  return (LoopState){window, pallete, window.initalized};
}

void LoopProcessInput(LoopState *state) {
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

void LoopRender(LoopState *state) {
  SDL_Renderer *renderer = state->window.renderer;
  SDL_Texture *texture = RGBPalleteCreateSDLTexture(&state->pallete, renderer);

  SDL_UpdateTexture(texture, NULL, state->pallete.buffer.buffer, 255 * (sizeof(uint32_t)));
  
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void LoopDestroy(LoopState *state) {
  RGBPalleteDestroy(&state->pallete);
  WindowDestroy(&state->window);
}

void processWindowEvent(SDL_WindowEvent *event, LoopState *state) {
  switch (event->event) {
    case SDL_WINDOWEVENT_CLOSE:
      state->isRunning = false;
      break;
    default:
      break;
  }
}

void processKeyDownEvent(SDL_KeyboardEvent *event, LoopState *state) {
  switch (event->keysym.sym) {
    case SDLK_ESCAPE:
      state->isRunning = false;
      break;
    case SDLK_DOWN:
      RGBPalleteDecrement(&state->pallete);
      break;
    case SDLK_UP:
      RGBPalleteIncrement(&state->pallete);
      break;
    default:
      break;
  }
}

void processMouseButtonUpEvent(SDL_MouseButtonEvent *event, LoopState* state) {
  uint8_t x, y;
  
  x = (((double) event->x / (double) state->window.width)) * 255;
  y = (((double) event->y / (double) state->window.height)) * 255;

  RGB color = RGBPalleteAt(&state->pallete, x, y);
  switch (event->button) {
    case SDL_BUTTON_LEFT:
      printf("RGB: [%d, %d, %d]\n", color.r, color.g, color.b);
      break;
    default:
      break;
  }
}
