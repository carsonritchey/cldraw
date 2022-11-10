#include "cldraw.h"

int main() {
  Canvas canvas = cl_get_canvas(cl_get_w(), cl_get_h() - 1);
  for(int i = 0; i < canvas.w * canvas.h; i++) {
    canvas.array[i] = cl_lum[rand() % cl_lum_count];
  }

  cl_clear();
  cl_draw_canvas(&canvas);

  cl_free_canvas(&canvas);
  return 0;
}