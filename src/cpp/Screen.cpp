#include <iostream>
#include <string>

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
    modifiers_vector = std::vector<std::string>(pixels, "");

    this->aspect = aspect;

    half_pixel_width = 1.0/(2.0*width); // in ndc space
    half_pixel_height = 1.0/(2.0*height); // in ndc space
    
    gradient_size = gradient.size();
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
    modifiers_vector = std::vector<std::string>(pixels, "");

    aspect = (width/height) / CHAR_ASPECT;

    half_pixel_width = 1.0/(2.0*width); // in ndc space
    half_pixel_height = 1.0/(2.0*height); // in ndc space
}

void Screen::print_buffer()
{
    for (int row=0; row<height; row++)
    {
        for (int col=0; col<width; col++)
        {
            // reset all ANSI modifiers relating to styles and colours
            std::cout << "\x1B[0m";

            int index = col + row*width;
            std::cout << modifiers_vector[index] << pixels_vector[index];
        }
        std::cout << std::endl;
    }
}

void Screen::clear_buffer()
{
    for (int i=0; i < pixels; i++)
    {
        pixels_vector[i] = EMPTY_CHAR;
        modifiers_vector[i] = "";
    }
}

bool Screen::set_pixel(int pixel_index, double brightness, double depth_percentage)
{
    if (pixel_index >= 0 && pixel_index < pixels)
    {
        int gradient_index = std::floor((std::max(brightness-0.0001,0.0)) * gradient_size);
        pixels_vector[pixel_index] = gradient[gradient_index];

        if (depth_percentage > 0.666)
            modifiers_vector[pixel_index] = "\u001b[2m";
        else if (depth_percentage > 0.333)
            modifiers_vector[pixel_index] = "";
        else
            modifiers_vector[pixel_index] = "\u001b[1m";

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
