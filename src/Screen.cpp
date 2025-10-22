#include <iostream>
#include "Screen.h"
#include "constants.h"

// apsect here is as standard i.e. w/h
Screen::Screen(int height, double aspect)
{
    this->height = height;
    width = height * aspect * CHAR_ASPECT;
    pixels = width * height;
    pixels_vector = std::vector<char>(pixels, EMPTY_CHAR);

    half_pixel_width = 1.0/(2.0*width); // in ndc space
    half_pixel_height = 1.0/(2.0*height); // in ndc space
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

int Screen::get_pixel_count() { return pixels; }

void Screen::pi_to_ndc(int pixel_index, double& ndc_x, double& ndc_y) const
{
    int row = pixel_index / width;
    int col = pixel_index % width;
    ndc_x = (col / static_cast<double>(width)) + half_pixel_width; 
    ndc_y = row / static_cast<double>(height) + half_pixel_height;
}

void Screen::clear_terminal()
{
    std::cout << "\x1B[H" << "\x1B[J";
}

void Screen::hide_cursor()
{
    std::cout << "\x1b[?25l";
}

void Screen::unhide_cursor()
{
    std::cout << "\x1b[?25h";
}
