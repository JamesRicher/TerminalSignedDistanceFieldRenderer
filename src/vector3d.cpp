#include <iostream>
#include "Vector3d.h"

float Vector3d::Length() const
{
    return std::sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}

Vector3d Vector3d::Normalize() const
{
    double len = this->Length();
    return Vector3d(x/len,y/len,z/len);
}

std::ostream& operator<<(std::ostream& os, const Vector3d& v)
{
    os << "(" << v.x<< ", " << v.y << ", " << v.z << ")";
    return os;
}

