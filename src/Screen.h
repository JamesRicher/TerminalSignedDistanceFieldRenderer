#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

class Screen
{
private:
    const char EMPTY_CHAR = '.';

    int width;
    int height;
    int pixels;
    std::vector<char> pixels_vector;
public:
    Screen(int width, int height);
    Screen(int height, double asepct);
    void print();
    void clear();
    bool set_pixel(int pixel_index, char c);
    static void clear_terminal();
};

#endif
