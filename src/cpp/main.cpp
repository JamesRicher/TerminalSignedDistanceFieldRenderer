#include <chrono>
#include <thread>
#include <cmath>
#include <csignal>
#include <list>

#include "Vector3d.h"
#include "sdf.h"
#include "Camera.h"
#include "Screen.h"
#include "constants.h"
#include "raymarch.h"
#include "light.h"

volatile bool STOP = false;
void sigint_handler(int sig);

int main()
{
    std::signal(SIGINT, sigint_handler);
    std::ios_base::sync_with_stdio(false);
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    //Screen screen = Screen(HEIGHT,ASPECT);
    Screen screen = Screen();
    Camera cam(HALF_FOV_DEG_X, screen.get_aspect());

    Screen::hide_cursor();

    // Setup lights
    std::list<Light> lights;
    lights.push_back(Light(Vector3d(1,1,1), 1.0));

    while(1)
    {
        if (STOP)
            break;

        screen.clear(); 
        for (int i=0; i < screen.get_pixel_count(); i++)
        {
            char pixel = check_pixel(i, screen, cam);
            if (pixel != screen.get_empty_char())
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
