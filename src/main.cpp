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

bool check_pixel(int pixel_index, Screen& screen, Camera& camera);
double scene(vector3d pos);

int main()
{
    int frames = 0;
    std::chrono::duration<double> frame_duration(FRAME_TIME);

    Screen screen(40,1.0);
    Camera cam(45.0, 45.0);

    while(1)
    {
        Screen::clear_terminal();

        screen.clear();

        for (int i=0; i < screen.get_pixel_count(); i++)
        {
            if (check_pixel(i, screen, cam))
                screen.set_pixel(i, '#');
        }
        screen.print();

        frames++;
        frames %= screen.get_pixel_count();

        std::this_thread::sleep_for(frame_duration);
    }

    return 0;
}

bool check_pixel(int pixel_index, Screen& screen, Camera& cam)
{
    double ndc_x, ndc_y;
    screen.pi_to_ndc(pixel_index, ndc_x, ndc_y);
    vector3d pixel_wpos = cam.ndc_to_world_pos(ndc_x, ndc_y);
    vector3d ro = cam.pos;
    vector3d rd = (pixel_wpos - ro).Normalize();
    
    double total_dist = 0.0;
    int step = 0;
    while (step < MAX_STEPS && total_dist < MAX_DIST)
    {
        double SDF_sample = scene(ro + rd*total_dist);
        if (SDF_sample < EPS)
            return true;

        total_dist += SDF_sample;
        step++;
    }
    return false;
}

double scene(vector3d pos)
{
    sdf_sphere(pos, 1.0, vector3d(0,0,4.0));
}