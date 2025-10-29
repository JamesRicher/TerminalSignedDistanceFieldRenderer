#ifndef RAYMARCH_H
#define RAYMARCH_H

#include "Screen.h"
#include "Camera.h"
#include "Vector3d.h"

class Raymarcher
{
private:
    const int MAX_STEPS = 200;
    const double MAX_DIST = 500.0; 
    const double EPS = 0.001;

public:
    // constructors
    Raymarcher(int steps, double dist, double eps);
    
    bool raymarch(Vector3d& cam_pos, Vector3d& pixel_pos, Vector3d& normal, double& dist);
    Vector3d get_normal(Vector3d pos);
    double scene(Vector3d pos);

    // getters
    double get_max_dist() { return MAX_DIST; }
};

#endif
