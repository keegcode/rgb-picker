#include "loop.h"

int main() {
  LoopState state = Loop_Setup();
  
  while (state.isRunning) {
    Loop_ProcessInput(&state);
    Loop_Render(&state);
  }
  
  Loop_Destroy(&state);

  return 0;
}


