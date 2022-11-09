#include "cldraw.h"

int main() {
  int w = cl_get_w();
  int h = cl_get_h() - 1;

  char* screen = cl_get_canvas(w, h);
  for(int i = 0; i < w * h; i++) {
    screen[i] = cl_lum[rand() % cl_lum_count];
  }

  cl_clear();
  cl_draw(screen, w, h);

  free(screen);
  return 0;
}