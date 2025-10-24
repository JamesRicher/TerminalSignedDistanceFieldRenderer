#include "Vector3d.h"
#include <cmath>

float sdf_sphere(Vector3d pos, float radius, Vector3d centre)
{
    return (pos - centre).Length() - radius;
}

float sdf_box(Vector3d pos, Vector3d box)
{
    Vector3d q = Vector3d::Abs(pos) - box; 
    return Vector3d::Max(q, 0.0).Length() + std::fmin(std::fmax(q.x, std::fmax(q.y, q.z)),0.0);
}

double op_union(double d1, double d2) { return std::min(d1,d2); }
double op_intersection(double d1, double d2) { return std::max(d1,d2); }
double op_subtraction(double d1, double d2) { return std::max(-d1,d2); }
double op_xor(double d1, double d2) { return std::max(std::min(d1,d2), -std::max(d1,d2)); }

double op_smooth_union(double d1, double d2, double k)
{
    k *= 4.0;
    double h = std::max(k-std::abs(d1-d2), 0.0);
    return std::min(d1,d2) - h*h*0.25/k;
}
