#pragma once

#include "lib.h"
#include "rgb-pallete.h"

typedef struct {
  Window window;
  RGBPallete pallete;
  bool isRunning;
} LoopState;

LoopState Loop_Setup();

void Loop_ProcessInput(LoopState *state);

void processWindowEvent(SDL_WindowEvent event, LoopState *state);
void processKeyDownEvent(SDL_KeyboardEvent event, LoopState *state);

void Loop_Render(LoopState* state);

void Loop_Destroy(LoopState* state);
