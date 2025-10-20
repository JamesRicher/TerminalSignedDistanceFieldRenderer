#include <cmath>
#include "constants.h"
#include "camera.h"

Camera::Camera(double x_fov_deg, double y_fov_deg)
{
    this->x_fov_rad = (x_fov_deg * PI)/180.0;
    this->y_fov_rad = (y_fov_deg * PI)/180.0;
    this->aspect = std::tan(x_fov_rad) / std::tan(y_fov_rad);

    pos = vector3d(0,0,0);
    facing = vector3d(0,0,1);
}

double Camera::get_aspect() const { return aspect; }
