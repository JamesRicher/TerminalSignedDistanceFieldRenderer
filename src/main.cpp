#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include "vector3d.h"
#include "SDF.h"
#include "camera.h"
#include "Screen.h"
#include "constants.h"
#include "raymarch.h"

// authored constants options
const int HEIGHT = 50;
const double ASPECT = 1.5; // final aspect ratio of the image
const double HALF_FOV_DEG_X = 45.0; // camera horizontal fov

int main()
{
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    Screen screen(HEIGHT,ASPECT);
    Camera cam(HALF_FOV_DEG_X, ASPECT);

    while(1)
    {
        Screen::clear_terminal();

        screen.clear();

        for (int i=0; i < screen.get_pixel_count(); i++)
        {
            if (check_pixel(i, screen, cam))
            {
                screen.set_pixel(i, '#');
            }
        }
        screen.print();
        std::this_thread::sleep_for(frame_duration);

    }

    return 0;
}