#include <iostream>
#include <chrono>
#include <thread>

#include "vector3d.h"
#include "SDF.h"

// constants
const int WIDTH = 20;
const int HEIGHT = 20;
const int PIXELS = HEIGHT * WIDTH;

const int FPS = 12;
const double FRAME_TIME = 1.0/static_cast<double>(FPS);

const float PI = 3.14159265359;

// camera constants
char screen[PIXELS];

void fill_with(char* ar, char c, int len);
void reset_screen();
void draw_scene();
void print_screen();

int main()
{
    int frames = 0;
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    while(1)
    {
        reset_screen();
        draw_scene();
        screen[frames] = '#';
        print_screen();

        frames++;
        frames %= PIXELS;

        std::this_thread::sleep_for(frame_duration);
    }

    return 0;
}

void fill_with(char* ar, char c, int len)
{
    for (int i = 0; i < len; i++)
        *(ar+i) = c;
}

void reset_screen()
{
    std::cout << "\033[2J\033[1;1H";
    fill_with(screen, '.', PIXELS);
}

void draw_scene()
{
    return;
}

void print_screen()
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col =0; col < WIDTH; col++)
        {
            std::cout << screen[col + row*WIDTH];
        }
         std::cout << std::endl;
    }
}
