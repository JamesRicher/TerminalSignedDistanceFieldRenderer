#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include "vector3d.h"
#include "SDF.h"
#include "camera.h"
#include "Screen.h"
#include "constants.h"

const double x_fov_angle = 45.0;
const double y_fov_angle = 45.0;
const double apsect = std::tan(x_fov_angle) / std::tan(y_fov_angle);
const double character_apsect = 2.0;

const int WIDTH = 20;
const int HEIGHT = 20;
const int PIXELS = HEIGHT * WIDTH;

int main()
{
    int frames = 0;
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    Screen screen(20,20);

    while(1)
    {
        Screen::clear_terminal();

        screen.clear();
        screen.set_pixel(frames, '#');
        screen.print();

        frames++;
        frames %= PIXELS;

        std::this_thread::sleep_for(frame_duration);
    }

    return 0;
}