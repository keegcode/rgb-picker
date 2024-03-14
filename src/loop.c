#include "loop.h"
#include "rgb-pallete.h"

LoopState Loop_Setup() {
  Window window = createWindow();
  RGBPallete pallete = {0xFFFF0000, 0xFFFF0000, 15};
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
          processWindowEvent(event.window, state);
          break;
        case SDL_KEYDOWN:
          processKeyDownEvent(event.key, state);
          break;
        default:
          break;
      }
    }
}

void Loop_Render(LoopState *state) {
  uint32_t *buffer = state->window.colorBuffer.buffer;
  SDL_Renderer *renderer = state->window.renderer;
  SDL_Texture *texture = RGBPallete_CreateSDLTexture(&state->pallete, renderer, buffer);

  SDL_UpdateTexture(texture, NULL, buffer, 255 * (sizeof(uint32_t)));
  
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void Loop_Destroy(LoopState *state) {
  destroyWindow(&state->window);
}

void processWindowEvent(SDL_WindowEvent event, LoopState* state) {
  switch (event.event) {
    case SDL_WINDOWEVENT_CLOSE:
      state->isRunning = false;
      break;
    default:
      break;
  }
}

void processKeyDownEvent(SDL_KeyboardEvent event, LoopState* state) {
  switch (event.keysym.sym) {
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
