#include "Screen.h"
#include "camera.h"
#include "constants.h"
#include "SDF.h"
#include "raymarch.h"

bool check_pixel(int pixel_index, Screen& screen, Camera& cam, double cur_time)
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
        double SDF_sample = scene(ro + rd*total_dist, cur_time);
        if (SDF_sample < EPS)
            return true;

        total_dist += SDF_sample;
        step++;
    }
    return false;
}

double scene(vector3d pos, double cur_time)
{
    double offset = std::sin(cur_time);
    return sdf_sphere(pos, 1.0, vector3d(0,0 + offset,4.0));
}