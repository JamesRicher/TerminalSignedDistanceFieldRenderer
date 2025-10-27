#include <iostream>

// only need these for getting screen width and height
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO

#include "Screen.h"
#include "constants.h"

// apsect here is as standard i.e. w/h
Screen::Screen(int height, double aspect)
{
    this->height = height;
    width = height * aspect * CHAR_ASPECT;
    pixels = width * height;
    pixels_vector = std::vector<char>(pixels, EMPTY_CHAR);

    this->aspect = aspect;

    half_pixel_width = 1.0/(2.0*width); // in ndc space
    half_pixel_height = 1.0/(2.0*height); // in ndc space
}

// makes fullscreen
Screen::Screen()
{
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    height = size.ws_row;
    width = size.ws_col;

    pixels = width * height;
    pixels_vector = std::vector<char>(pixels, EMPTY_CHAR);

    aspect = (width/height) / CHAR_ASPECT;

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

bool Screen::set_pixel(int pixel_index, double brightness)
{
    // get the corresponding char
    brightness = std::pow(brightness,2);
    int ASCII_index = std::floor(brightness * 7);
    char c = gradient.c_str()[ASCII_index];

    if (pixel_index >= 0 && pixel_index < pixels)
    {
        pixels_vector[pixel_index] = c;
        return true;
    }
    return false;
}

void Screen::pi_to_ndc(int pixel_index, double& ndc_x, double& ndc_y) const
{
    int row = pixel_index / width;
    int col = pixel_index % width;
    ndc_x = (col / static_cast<double>(width)) + half_pixel_width; 
    ndc_y = row / static_cast<double>(height) - half_pixel_height;
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
