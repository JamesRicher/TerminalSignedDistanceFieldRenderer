#include "vector3d.h"
#include <cmath>

float sdf_sphere(vector3d pos, float radius, vector3d centre)
{
    return (pos - centre).Length() - radius;
}

float sdf_box(vector3d pos, vector3d box)
{
    vector3d q = vector3d::Abs(pos) - box; 
    return vector3d::Max(q, 0.0).Length() + std::fmin(std::fmax(q.x, std::fmax(q.y, q.z)),0.0);
}
