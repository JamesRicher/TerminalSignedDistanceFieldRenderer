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
    lights.push_back(Light(Vector3d(0,0,1), 1.0));

    while(1)
    {
        if (STOP)
            break;

        screen.clear(); 
        for (int i=0; i < screen.get_pixel_count(); i++)
        {
            Vector3d normal;
            bool hit = check_pixel(i, screen, cam, normal);
            if (hit)
            {
                double diffuse = lights.front().calculate_diffuse(normal);
                if (diffuse > 0.9)
                {
                    screen.set_pixel(i, '@');
                }
                else if (diffuse > 0.5)
                {
                    screen.set_pixel(i, 'c');
                }
                else
                {
                    screen.set_pixel(i, '.');
                }   
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
