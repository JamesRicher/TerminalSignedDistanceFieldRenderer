#include <chrono>
#include "Screen.h"
#include "camera.h"
#include "constants.h"
#include "SDF.h"
#include "raymarch.h"
#include "vector3d.h"

char check_pixel(int pixel_index, Screen& screen, Camera& cam)
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
        vector3d sample_pos = ro +rd*total_dist;
        double SDF_sample = scene(sample_pos);
        if (SDF_sample < EPS)
        {
            vector3d normal = get_normal(sample_pos);
            double diffuse = normal.Dot(vector3d(1,1,1));
            if (diffuse >= 0.5)
                return '#';
            else
                return 'c';
        }

        total_dist += SDF_sample;
        step++;
    }
    return 'q';
}

vector3d get_normal(vector3d pos)
{
    double eps = 0.0001;
    double x = scene(pos + vector3d(eps,0.0,0.0)) - scene(pos - vector3d(eps,0.0,0.0));
    double y = scene(pos + vector3d(0.0,eps,0.0)) - scene(pos - vector3d(0.0,eps,0.0));
    double z = scene(pos + vector3d(0.0,0.0,eps)) - scene(pos - vector3d(0.0,0.0,eps));
    return vector3d(x,y,z).Normalize();
}

double scene(vector3d pos)
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = now - START_TIME;
    double cur_time = diff.count();

    double offset1 = std::sin(cur_time*3.0);
    double offset2 = std::sin(cur_time*1.712);
    float sphere1 = sdf_sphere(pos, 0.5, vector3d(0,0+offset1,4.0));
    float sphere2 = sdf_sphere(pos, 1.2, vector3d(0,0-offset2,4.0));
    return op_smooth_union(sphere1, sphere2, 0.1);
}
