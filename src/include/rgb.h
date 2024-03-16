#include "lib.h"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB;

RGB RGBFromU32(uint32_t color);
uint32_t RGBToU32(RGB *rgb);
RGB RGBLerp(RGB *rgb1, RGB *rgb2, double t);
uint32_t RGBU32Lerp(uint32_t color1, uint32_t color2, double t);

