#include <cmath>
#include "constants.h"
#include "camera.h"

Camera::Camera(double x_fov_deg, double y_fov_deg)
{
    x_fov_rad = (x_fov_deg * PI)/180.0;
    y_fov_rad = (y_fov_deg * PI)/180.0;

    near_plane_width = 2.0*std::tan(x_fov_rad);
    near_plane_height = 2.0*std::tan(y_fov_rad);

    aspect = near_plane_width / near_plane_height;

    pos = vector3d(0,0,0);
}

double Camera::get_aspect() const { return aspect; }

vector3d Camera::ndc_to_world_pos(double ndc_x, double ndc_y)
{
    double x = ndc_x * near_plane_width;
    double y = ndc_y * near_plane_height;
    return vector3d(x,y,1) + pos;
}