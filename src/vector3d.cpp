#include <iostream>
#include "vector3d.h"

float vector3d::Length() const
{
    return std::sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}

vector3d vector3d::Normalize() const
{
    double len = this->Length();
    return vector3d(x/len,y/len,z/len);
}

std::ostream& operator<<(std::ostream& os, const vector3d& v)
{
    os << "(" << v.x<< ", " << v.y << ", " << v.z << ")";
    return os;
}

