#ifndef CLDRAW_H_
#define CLDRAW_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ASCII luminescence gradient (assuming terminal uses white text & black background)
const char cl_lum[]     = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'}; // black -> white
const int  cl_lum_count = 10;

/* basic functions */

// returns the current terminal width (number of columns)
int cl_get_w() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_col;
}

// returns the current terminal height (number of rows)
int cl_get_h() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_row;
}

// moves cursor to (x, y)
void cl_goto(int x, int y) { printf("\033[%d;%dH", y, x); }

// clears the terminal
void cl_clear() { printf("\033[H\033[J"); }


/* canvas functions */
typedef struct {
    int w, h;
    char* array;
} Canvas;

// writes all characters of chars to terminal, given a width and height
void cl_draw_canvas(Canvas* c) {
    char line[c->w];
    for(int j = 0; j < c->h; j++) {
        for(int i = 0; i < c->w; i++) {
            line[i] = c->array[j * c->w + i];
        }

        if(j < c->h)
            printf("%s\n", line);
        else
            printf("%s", line);
    }
}

// returns Canvas* of size w * h
// must be freed after use
Canvas cl_get_canvas(int w, int h) {
    Canvas c;
    
    c.w = w;
    c.h = h;

    c.array = (char*)malloc(w * h * sizeof(char));
    for(int i = 0; i < w * h; i++) c.array[i] = ' ';

    return c;
}

// frees canvas' char*
void cl_free_canvas(Canvas* c) {
    free(c->array);
}

// assigns char ch at (x, y) to Canvas c
void cl_put_char(Canvas* c, int x, int y, char ch) {
    c->array[y * c->w + x] = ch;
}

// writes char* str at (x, y) to Canvas c
void cl_put_str(Canvas* c, int str_len, int x, int y, char* str) {
    for(int i = 0; i < str_len; i++) {
        c->array[y * c->w + x + i] = str[i];
    }
}

// draws a line from (x1, y1) to (x2, y2) with the character ch
void cl_line(Canvas* c, int x1, int y1, int x2, int y2, char ch) {
    cl_put_char(c, x1, y1, ch);
    cl_put_char(c, x2, y2, ch);
}

#endif