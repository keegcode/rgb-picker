#pragma once

#include "lib.h"
#include "rgb-pallete.h"

typedef struct {
  Window window;
  RGBPallete pallete;
  bool isRunning;
} LoopState;

LoopState LoopSetup();

void LoopProcessInput(LoopState *state);

void LoopRender(LoopState *state);

void LoopDestroy(LoopState *state);

void processWindowEvent(SDL_WindowEvent *event, LoopState *state);
void processKeyDownEvent(SDL_KeyboardEvent *event, LoopState *state);
void processMouseButtonUpEvent(SDL_MouseButtonEvent *event, LoopState *state);
