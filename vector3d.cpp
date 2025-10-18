#include <iostream>
#include "vector3d.h"

float vector3d::Length()
{
    return std::sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}

std::ostream& operator<<(std::ostream& os, const vector3d& v)
{
    os << "(" << v.x<< ", " << v.y << ", " << v.z << ")";
    return os;
}

