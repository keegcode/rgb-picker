#include "lib.h"

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} RGB;

RGB RGB_from_uint32_t(uint32_t color);
uint32_t RGB_to_uint32_t(RGB *rgb);
RGB RGB_Lerp(RGB *rgb1, RGB *rgb2, double t);
uint32_t RGB_uint32_t_Lerp(uint32_t color1, uint32_t color2, double t);

