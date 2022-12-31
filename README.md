# cldraw
a simple, single-file, header-only library for drawing to the terminal in C

# example usage

```
#include "cldraw.h"

int main() {
  // gets screen width and height
  int w = cl_get_w(), h = cl_get_h();
  
  // creates canvas to be drawn to
  Canvas canvas = cl_get_canvas(w, h);
  
  // writes smiley face onto center of canvas
  cl_put_str(&canvas, 2, w / 2, h / 2, ":)");
  
  // prints canvas to terminal
  cl_draw_canvas(&canvas);
  
  // frees canvas from memory
  cl_free_canvas(&canvas);
  return 0;
}
```
