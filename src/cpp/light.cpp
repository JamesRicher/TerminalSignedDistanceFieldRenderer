#include <algorithm>
#include "Vector3d.h"
#include "light.h"

Light::Light(Vector3d direction, double strength)
{
    this->direction = direction.Normalize();
    this->strength = strength;
}

double Light::calculate_diffuse(Vector3d normal)
{
    double diffuse = direction.Dot(normal) * strength; 
    return std::max(0.0,diffuse);
}
