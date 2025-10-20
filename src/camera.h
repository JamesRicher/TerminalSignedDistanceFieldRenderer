#ifndef CAMERA_H
#define CAMERA_H

#include "vector3d.h"

// assuming the near plane is at z=1 in view space and that 
// the camera is facing in the postive z with no rotation
class Camera
{
private:
    double x_fov_rad;
    double y_fov_rad;

    double near_plane_width;
    double near_plane_height;

    double aspect;


public:
    vector3d pos;

    Camera(double x_fov_deg, double y_fov_deg);

    double get_aspect() const;
    vector3d ndc_to_world_pos(double ndc_x, double ndc_y);
};

#endif
