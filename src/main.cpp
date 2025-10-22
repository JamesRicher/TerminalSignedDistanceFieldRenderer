#include <chrono>
#include <thread>
#include <cmath>
#include <csignal>

#include "vector3d.h"
#include "SDF.h"
#include "camera.h"
#include "Screen.h"
#include "constants.h"
#include "raymarch.h"

volatile bool STOP = false;
void sigint_handler(int sig);

int main()
{
    signal(SIGINT, sigint_handler);

    std::ios_base::sync_with_stdio(false);
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    Screen screen(HEIGHT,ASPECT);
    Camera cam(HALF_FOV_DEG_X, ASPECT);

    Screen::hide_cursor();

    while(1)
    {
        if (STOP)
            break;

        screen.clear();

        for (int i=0; i < screen.get_pixel_count(); i++)
        {
            char pixel = check_pixel(i, screen, cam);
            if (pixel != 'q')
            {
                screen.set_pixel(i, pixel);
            }
        }
        Screen::clear_terminal();
        screen.print();
        std::this_thread::sleep_for(frame_duration);
    }
    return 0;
}

void sigint_handler(int sig)
{
    Screen::unhide_cursor();
    STOP = true;
}
