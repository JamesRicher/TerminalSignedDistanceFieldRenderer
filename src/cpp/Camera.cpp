#include <cmath>
#include "constants.h"
#include "Camera.h"
#include "Vector3d.h"

Camera::Camera(double half_fov_deg_x, double aspect, Vector3d pos)
{
    this->half_fov_rad_x = (half_fov_deg_x * PI)/180.0;

    near_plane_width = 2.0*std::tan(half_fov_rad_x);
    near_plane_height = near_plane_width * (1.0/aspect);

    this->pos = pos;

    forward = Vector3d(0,0,1.0);
    up = Vector3d(0,1.0,0);
    right = Vector3d::Cross(up, forward);  
}

Vector3d Camera::ndc_to_world_pos(double ndc_x, double ndc_y)
{
    Vector3d view_space_pos = forward + 
        right * (ndc_x-0.5)*near_plane_width +
        up * (ndc_y-0.5)*near_plane_height;

    Vector3d world_space_pos = view_space_pos + pos;
    return world_space_pos;
}

void Camera::rotate(char axis, double ang)
{
    switch (axis)
    {
        case 'x':
            forward = forward.rotate_x(ang);
            up = up.rotate_x(ang);
            right = right.rotate_x(ang);
            break;
        case 'y':
            forward = forward.rotate_y(ang);
            up = up.rotate_y(ang);
            right = right.rotate_y(ang);
            break;
        case 'z':
            forward = forward.rotate_z(ang);
            up = up.rotate_z(ang);
            right = right.rotate_z(ang);
            break;
        default:
            break;
    }
}
