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
#include "graphics_context.h"

volatile bool STOP = false;
void sigint_handler(int sig);

int main()
{
    std::signal(SIGINT, sigint_handler);
    std::ios_base::sync_with_stdio(false);
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    GraphicsContext gc = GraphicsContext(HEIGHT, ASPECT, HALF_FOV_DEG_X, Vector3d(0,0,0),
                                         100, 500.0, 0.001);

    Screen::hide_cursor();

    // Setup lights
    std::list<Light> lights;
    lights.push_back(Light(Vector3d(1,1,1), 1.0));

    while(1)
    {
        if (STOP)
            break;

        gc.draw_frame();

        std::this_thread::sleep_for(frame_duration);
    }
    return 0;
}

void sigint_handler(int sig)
{
    Screen::unhide_cursor();
    STOP = true;
}
