#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3d.h"

// assuming the near plane is at z=1 in view space and that 
// the Camera is facing in the postive z with no rotation
class Camera
{
private:
    double half_fov_rad_x;

    double near_plane_width;
    double near_plane_height;

    Vector3d forward;
    Vector3d up;
    Vector3d right;

public:
    Vector3d pos;

    inline Vector3d get_right() { return right; }
    Camera(double x_fov_deg, double y_fov_deg, Vector3d pos);

    void rotate(char axis, double ang);
    Vector3d ndc_to_world_pos(double ndc_x, double ndc_y);
};

#endif
