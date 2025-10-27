#include <chrono>
#include "Screen.h"
#include "Camera.h"
#include "constants.h"
#include "sdf.h"
#include "raymarch.h"
#include "Vector3d.h"
#include "scenes.h"

bool check_pixel(int pixel_index, Screen& screen, Camera& cam, Vector3d& normal)
{
    double ndc_x, ndc_y;
    screen.pi_to_ndc(pixel_index, ndc_x, ndc_y);
    Vector3d pixel_wpos = cam.ndc_to_world_pos(ndc_x, ndc_y);
    Vector3d ro = cam.pos;
    Vector3d rd = (pixel_wpos - ro).Normalize();
    
    double total_dist = 0.0;
    int step = 0;
    while (step < MAX_STEPS && total_dist < MAX_DIST)
    {
        Vector3d sample_pos = ro +rd*total_dist;
        double SDF_sample = scene(sample_pos);
        if (SDF_sample < EPS)
        {
            normal = get_normal(sample_pos);
            return true;
        }

        total_dist += SDF_sample;
        step++;
    }
    return false;
}

Vector3d get_normal(Vector3d pos)
{
    double eps = 0.0001;
    double x = scene(pos + Vector3d(eps,0.0,0.0)) - scene(pos - Vector3d(eps,0.0,0.0));
    double y = scene(pos + Vector3d(0.0,eps,0.0)) - scene(pos - Vector3d(0.0,eps,0.0));
    double z = scene(pos + Vector3d(0.0,0.0,eps)) - scene(pos - Vector3d(0.0,0.0,eps));
    return Vector3d(x,y,z).Normalize() * -1.0;
}


double scene(Vector3d pos)
{
    return radial_spheres(pos);
}
