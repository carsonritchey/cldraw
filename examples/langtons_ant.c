#include <unistd.h>

#include "cldraw.h"

int main() {
  int w = cl_get_w();
  int h = cl_get_h() - 1;
  char* screen = cl_get_canvas(w, h);

  int plane[w * h];
  for(int i = 0; i < w * h; plane[i++] = 0);

  // 0 = left, 1 = up, 2 = right, 3 = down
  int dir = 0;
  int x = w / 2 - 1;
  int y = h / 2 - 1;

  for(int i = 0; x < w && y < h && x >= 0 && y >= 0; i++) {
    if(!plane[w * y + x]) {
      plane[w * y + x] = 1;
      dir = (dir + 1) % 4;
    } else {
      plane[w * y + x] = 0;
      dir = ((dir - 1) + 4) % 4;
    }

    if(dir == 0) x--;
    if(dir == 1) y--;
    if(dir == 2) x++;
    if(dir == 3) y++;

    for(int i = 0; i < w * h; i++) screen[i] = (plane[i]) ? '#' : ' ';
    screen[w * y + x] = 'A';
    cl_goto(0, 0);
    printf("iteration %d", i);

    cl_clear();
    cl_draw(screen, w, h);

    usleep(500 * 1000);
  }

  free(screen);
  return 0;
}