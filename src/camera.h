#ifndef CAMERA_H
#define CAMERA_H

#include "vector3d.h"

class Camera
{
private:
    double x_fov_rad;
    double y_fov_rad;
    double aspect;

public:
    vector3d pos;
    vector3d facing;
    Camera(double x_fov_deg, double y_fov_deg);
    double get_aspect() const;
};

#endif
