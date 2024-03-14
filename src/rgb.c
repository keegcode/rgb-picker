#include "include/rgb.h"

RGB RGB_from_uint32_t(uint32_t color) {
  RGB colors;
  
  unsigned char r = (color >> 16) & 0xFF;
  unsigned char g = (color >> 8) & 0xFF;
  unsigned char b = color & 0xFF;
  
  colors.r = r; 
  colors.g = g;
  colors.b = b;

  return colors;
}

uint32_t RGB_to_uint32_t(RGB *rgb) {
  return 0xFF000000 | (rgb->r << 16) | (rgb->g << 8) | rgb->b;
}

RGB RGB_Lerp(RGB *rgb1, RGB *rgb2, double t) {
  unsigned char r = (unsigned char)(rgb1->r + (rgb2->r - rgb1->r) * t);
  unsigned char g = (unsigned char)(rgb1->g + (rgb2->g - rgb1->g) * t);
  unsigned char b = (unsigned char)(rgb1->b + (rgb2->b - rgb1->b) * t);

  return (RGB) {r,g,b};
}

uint32_t RGB_uint32_t_Lerp(uint32_t color1, uint32_t color2, double t) {
  RGB rgb1 = RGB_from_uint32_t(color1);
  RGB rgb2 = RGB_from_uint32_t(color2);
  
  RGB lerp = RGB_Lerp(&rgb1, &rgb2, t);

  return RGB_to_uint32_t(&lerp);
}
