#include "include/rgb.h"

RGB RGBFromU32(uint32_t color) {
  RGB colors;
  
  unsigned char r = (color >> 16) & 0xFF;
  unsigned char g = (color >> 8) & 0xFF;
  unsigned char b = color & 0xFF;
  
  colors.r = r; 
  colors.g = g;
  colors.b = b;

  return colors;
}

uint32_t RGBToU32(RGB *rgb) {
  return 0xFF000000 | (rgb->r << 16) | (rgb->g << 8) | rgb->b;
}

RGB RGBLerp(RGB *rgb1, RGB *rgb2, double t) {
  unsigned char r = (unsigned char)(rgb1->r + (rgb2->r - rgb1->r) * t);
  unsigned char g = (unsigned char)(rgb1->g + (rgb2->g - rgb1->g) * t);
  unsigned char b = (unsigned char)(rgb1->b + (rgb2->b - rgb1->b) * t);

  return (RGB) {.r=r,.g=g,.b=b};
}

uint32_t RGBU32Lerp(uint32_t color1, uint32_t color2, double t) {
  RGB rgb1 = RGBFromU32(color1);
  RGB rgb2 = RGBFromU32(color2);
  
  RGB lerp = RGBLerp(&rgb1, &rgb2, t);

  return RGBToU32(&lerp);
}
