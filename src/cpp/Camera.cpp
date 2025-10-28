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
}

Vector3d Camera::ndc_to_world_pos(double ndc_x, double ndc_y)
{
    double x = (ndc_x-0.5) * near_plane_width;
    double y = -(ndc_y-0.5) * near_plane_height;
    return Vector3d(x,y,1) + pos;
}
