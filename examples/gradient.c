#include <math.h>

#include "cldraw.h"

int main() {
  int w = cl_get_w();
  int h = cl_get_h() - 1;

  int cx = w / 2;
  int cy = h / 2;
  
  float max_distance = sqrt(pow(abs(cx - w - 1), 2) + pow(abs(cy - h - 1), 2));

  Canvas canvas = cl_get_canvas(w, h);
  for(int j = 0; j < h; j++) {
    for(int i = 0; i < w; i++) {
      float distance = sqrt(pow(abs(cx - i), 2) + pow(abs(cy - j), 2));
      int lum = round(distance / max_distance * cl_lum_count);

      canvas.array[w * j + i] = cl_lum[lum];
    }
  }

  cl_clear();
  cl_draw_canvas(&canvas);

  cl_free_canvas(&canvas);
  return 0;
}