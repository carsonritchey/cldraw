#include <math.h>

#include "cldraw.h"

int main() {
  int w = cl_get_w();
  int h = cl_get_h() - 1;

  int cx = w / 2;
  int cy = h / 2;
  
  float max_distance = sqrt(pow(abs(cx - w - 1), 2) + pow(abs(cy - h - 1), 2));

  char* screen = cl_get_array(w, h);
  for(int j = 0; j < h; j++) {
    for(int i = 0; i < w; i++) {
      float distance = sqrt(pow(abs(cx - i), 2) + pow(abs(cy - j), 2));
      int lum = round(distance / max_distance * cl_lum_count);

      screen[w * j + i] = cl_lum[lum];
    }
  }

  cl_clear();
  cl_draw(screen, w, h);

  free(screen);
  return 0;
}