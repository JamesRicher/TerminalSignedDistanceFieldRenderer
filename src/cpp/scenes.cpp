#include <chrono>
#include <cmath>
#include "sdf.h"
#include "Vector3d.h"
#include "constants.h"

double get_current_time();

double two_boxes_and_sphere(Vector3d pos)
{
    double cur_time = get_current_time();
    double morph = 0.15;
    Vector3d box_size = Vector3d(0.5,0.5,1);

    double box1 = sdf_box(pos - Vector3d(-1.5,0,3), box_size);
    double box2 = sdf_box(pos - Vector3d(1.5,0,3), box_size);
    double box3 = sdf_box(pos - Vector3d(0,1.5,3), box_size);
    double box4 = sdf_box(pos - Vector3d(0,-1.5,3), box_size);
    double u = op_smooth_union(box1,box2,morph);
    u = op_smooth_union(box3,u, morph);
    u = op_smooth_union(box4,u,morph);

    double speed = 2.0;
    Vector3d sphere_pos = Vector3d(1.5*std::sin(speed * cur_time), 1.5*std::cos(speed * cur_time), 3);
    double sphere = sdf_sphere(pos - sphere_pos, 1);
    u = op_smooth_union(sphere, u, morph);

    return u;
}

double spheres_around_a_cube(Vector3d pos)
{
    double cur_time = get_current_time();

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

double radial_spheres(Vector3d pos)
{
    double cur_time = get_current_time();
    int sphere_count = 3;
    double radius = 0.7;

    Vector3d box_pos = Vector3d(0,0,6);
    double u = sdf_box((pos-box_pos).rotate_x(cur_time*50.0), Vector3d(0.5,0.5,0.5));
    double move_radius = 3.0;
    double morph = 0.1;

    double interpolation = (std::sin(cur_time) + 1.0)/2.0;
    for (int i=0; i < sphere_count; i++)
    {
        double ang = 2*PI * i/static_cast<double>(sphere_count); 
        Vector3d endpoint = Vector3d(std::sin(ang), std::cos(ang),0) * interpolation * move_radius + box_pos; 
        double s = sdf_sphere(pos - endpoint, radius);
        u = op_smooth_union(u,s,morph);
    }

    return u;
}

double near_plane_test(Vector3d pos)
{
    double cur_time = get_current_time();
    Vector3d c = Vector3d(0,0,cur_time);
    double u = sdf_sphere(pos - c, 1.0);
    return u;
}

double infinite_spheres(Vector3d pos)
{
    Vector3d offset = Vector3d(1.5,1.5,1.5);
    Vector3d new_pos = repeat_coords(pos - offset, Vector3d(3,3,3));// + Vector3d(1.5,0,1.5);
    return sdf_sphere(new_pos, 0.7);
}


double get_current_time()
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = now - START_TIME;
    double cur_time = diff.count();
    
    return cur_time;
}
