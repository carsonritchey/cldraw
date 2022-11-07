#ifndef CLDRAW_H_
#define CLDRAW_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ASCII luminescence gradient (assuming terminal uses white text & black background)
const char cl_lum[]     = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'}; // black -> white
const int  cl_lum_count = 10;

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

// writes all characters of chars to terminal, given a width and height
void cl_draw(char* chars, int w, int h) {
    char line[w];
    for(int j = 0; j < h; j++) {
        for(int i = 0; i < w; i++) {
            line[i] = chars[j * w + i];
        }

        if(j < h)
            printf("%s\n", line);
        else
            printf("%s", line);
    }
}

// moves cursor to (x, y)
void cl_goto(int x, int y) { printf("\033[%d;%dH", y, x); }

// clears the terminal
void cl_clear() { printf("\033[H\033[J"); }

// returns char* to array of size w * h
// must be freed after use
char* cl_get_array(int w, int h) {
    char* array = (char*)malloc(w * h * sizeof(char));
    for(int i = 0; i < w * h; i++) array[i] = ' ';

    return array;
}

#endif