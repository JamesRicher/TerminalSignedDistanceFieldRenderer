#include <chrono>
#include "Screen.h"
#include "Camera.h"
#include "constants.h"
#include "SDF.h"
#include "raymarch.h"
#include "Vector3d.h"

char check_pixel(int pixel_index, Screen& screen, Camera& cam)
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
            Vector3d normal = get_normal(sample_pos);
            double diffuse = normal.Dot(Vector3d(0,1,-1));
            if (diffuse >= 0.9)
                return '#';
            else if (diffuse >= 0.5)
                return 'c';
            else
                return '.';
        }

        total_dist += SDF_sample;
        step++;
    }
    return screen.get_empty_char(); 
}

Vector3d get_normal(Vector3d pos)
{
    double eps = 0.0001;
    double x = scene(pos + Vector3d(eps,0.0,0.0)) - scene(pos - Vector3d(eps,0.0,0.0));
    double y = scene(pos + Vector3d(0.0,eps,0.0)) - scene(pos - Vector3d(0.0,eps,0.0));
    double z = scene(pos + Vector3d(0.0,0.0,eps)) - scene(pos - Vector3d(0.0,0.0,eps));
    return Vector3d(x,y,z).Normalize();
}

double scene(Vector3d pos)
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = now - START_TIME;
    double cur_time = diff.count();

    double offset1 = std::sin(cur_time*3.0);
    double offset2 = std::sin(cur_time*1.712);
    // float sphere1 = sdf_sphere(pos, 0.5, Vector3d(0,0+offset1,4.0));
    // float sphere2 = sdf_sphere(pos, 1.2, Vector3d(0,0-offset2,4.0));
    // return op_smooth_union(sphere1, sphere2, 0.1);
    
    /* 
    double sphere1 = sdf_sphere(pos, 1, Vector3d(0+offset1,0,4.0));
    double sphere2 = sdf_sphere(pos, 1, Vector3d(3-offset1-offset2,0,4.0));
    double sphere3 = sdf_sphere(pos, 1, Vector3d(-3+offset2,0,4.0));
    double sphere4 = sdf_sphere(pos, 1, Vector3d(0,0,8.0+offset1));
    double sphere5 = sdf_sphere(pos, 1, Vector3d(3,0+offset2,8.0));
    double sphere6 = sdf_sphere(pos, 1, Vector3d(-3+offset2-offset1,0,8.0));
    double u = op_smooth_union(sphere1, sphere2,0.3);
    u = op_smooth_union(u, sphere3,0.3);
    u = op_smooth_union(u, sphere4,0.3);
    u = op_smooth_union(u, sphere5,0.3);
    u = op_smooth_union(u, sphere6,0.3);
    
    double morph = 0.3;

    double box = sdf_box(pos + Vector3d(2,1,-4), Vector3d(0.5,0.5,1));
    double sphere = sdf_sphere(pos, 0.9, Vector3d(offset1,offset2,4));
    double box2 = sdf_box(pos + Vector3d(-2,1,-4), Vector3d(0.5,0.5,1));
    double u2 = op_smooth_union(box, sphere, morph);
    u2 = op_smooth_union(box2, u2, morph);
    return u2;
    */

    double morph = 0.2;
    Vector3d sphere1_centre = Vector3d(-1,0,3);
    Vector3d sphere1_offset = Vector3d(std::sin(-cur_time * 1.5), std::cos(-cur_time * 1.5), 0);
    Vector3d sphere2_centre = Vector3d(1,0,3);
    Vector3d sphere2_offset = Vector3d(std::sin(cur_time * 1.5), std::cos(cur_time * 1.5), 0);
    double sphere1 = sdf_sphere(pos - (sphere1_centre + sphere2_offset), 0.5);
    double sphere2 = sdf_sphere(pos - (sphere2_centre - sphere2_offset), 0.5);
    double sphere3 = sdf_sphere(pos - (sphere1_centre - sphere1_offset), 0.5);
    double sphere4 = sdf_sphere(pos - (sphere2_centre + sphere1_offset), 0.5);

    double box = sdf_box((pos- Vector3d(0,0,3)).rotate_x(cur_time * 50.0), Vector3d(0.5,0.5,0.5));

    double u = op_smooth_union(sphere1, sphere2, morph);
    u = op_smooth_union(u, sphere3, morph);
    u = op_smooth_union(u, sphere4, morph);
    u = op_smooth_union(u, box, morph);
    return u;
}
