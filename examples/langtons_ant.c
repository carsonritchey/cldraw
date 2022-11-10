#include <unistd.h>

#include "cldraw.h"

int main() {
    Canvas canvas = cl_get_canvas(cl_get_w(), cl_get_h() - 1);

    char on = '#', off = ' ';
    
    // 0 = left, 1 = up, 2 = right, 3 = down
    int dir = 0;
    int x = canvas.w / 2 - 1;
    int y = canvas.h / 2 - 1;

    while(x < canvas.w && y < canvas.h && x >= 0 && y >= 0) {
        if(canvas.array[canvas.w * y + x] == off) {
            canvas.array[canvas.w * y + x] = on;
            dir = (dir + 1) % 4;
        } else {
            canvas.array[canvas.w * y + x] = off;
            dir = ((dir - 1) + 4) % 4;
        }

        if(dir == 0) x--;
        else if(dir == 1) y--;
        else if(dir == 2) x++;
        else if(dir == 3) y++;

        cl_draw_canvas(&canvas);
        usleep(50 * 1000);
    }

    cl_free_canvas(&canvas);
    return 0;
}