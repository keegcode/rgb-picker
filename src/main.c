#include "include/loop.h"

int main() {
  LoopState state = LoopSetup();

  while (state.isRunning) {
    LoopProcessInput(&state);
    LoopRender(&state);
  }

  LoopDestroy(&state);

  return 0;
}


