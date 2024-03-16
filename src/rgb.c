#include "include/rgb.h"

RGB RGBFromU32(uint32_t color) {
  RGB colors;
  
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >> 8) & 0xFF;
  uint8_t b = color & 0xFF;
  
  colors.r = r; 
  colors.g = g;
  colors.b = b;

  return colors;
}

uint32_t RGBToU32(RGB *rgb) {
  return 0xFF000000 | (rgb->r << 16) | (rgb->g << 8) | rgb->b;
}

RGB RGBLerp(RGB *rgb1, RGB *rgb2, double t) {
  uint8_t r = (uint8_t)(rgb1->r + (rgb2->r - rgb1->r) * t);
  uint8_t g = (uint8_t)(rgb1->g + (rgb2->g - rgb1->g) * t);
  uint8_t b = (uint8_t)(rgb1->b + (rgb2->b - rgb1->b) * t);

  return (RGB) {.r=r,.g=g,.b=b};
}

uint32_t RGBU32Lerp(uint32_t color1, uint32_t color2, double t) {
  RGB rgb1 = RGBFromU32(color1);
  RGB rgb2 = RGBFromU32(color2);
  
  RGB lerp = RGBLerp(&rgb1, &rgb2, t);

  return RGBToU32(&lerp);
}
