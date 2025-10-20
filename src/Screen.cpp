#include <iostream>
#include "Screen.h"

Screen::Screen(int width, int height)
{
    this->width = width;
    this->height = height;
    pixels = width * height;
    pixels_vector = std::vector<char>(pixels, EMPTY_CHAR);
}

Screen::Screen(int width, double aspect)
{
    this->width = width;
    height = width * aspect;
    pixels = width * height;
    pixels_vector = std::vector<char>(pixels, EMPTY_CHAR);
}

void Screen::print()
{
    for (int row=0; row<height; row++)
    {
        for (int col=0; col<width; col++)
        {
            int index = col + row*width;
            std::cout << pixels_vector[index];
        }
        std::cout << std::endl;
    }
}

void Screen::clear()
{
    for (int i=0; i < pixels; i++)
        pixels_vector[i] = EMPTY_CHAR;
}

bool Screen::set_pixel(int pixel_index, char c)
{
    if (pixel_index >= 0 && pixel_index < pixels)
    {
        pixels_vector[pixel_index] = c;
        return true;
    }
    return false;
}

void Screen::clear_terminal()
{
    std::cout << "\033[2J\033[1;1H";
}
