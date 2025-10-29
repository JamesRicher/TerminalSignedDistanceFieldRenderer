#include <iostream>
#include <cmath>
#include "constants.h"
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

Vector3d Vector3d::rotate_x(double theta)
{
    theta /= DEG_TO_RAD; 
    double c_theta = std::cos(theta);
    double s_theta = std::sin(theta);
    double new_x = x;
    double new_y = c_theta*y - s_theta*z;
    double new_z = s_theta*y + c_theta*z;  
    
    return Vector3d(new_x, new_y, new_z);
}

Vector3d Vector3d::rotate_y(double theta)
{
    theta /= DEG_TO_RAD; 
    double c_theta = std::cos(theta);
    double s_theta = std::sin(theta);
    double new_x = c_theta*x + s_theta*z;;
    double new_y = y;
    double new_z = -s_theta*x + c_theta*z;  
    
    return Vector3d(new_x, new_y, new_z);
}

Vector3d Vector3d::rotate_z(double theta)
{
    theta /= DEG_TO_RAD; 
    double c_theta = std::cos(theta);
    double s_theta = std::sin(theta);
    double new_x = c_theta*x - s_theta*y;
    double new_y = s_theta*x + c_theta*y;
    double new_z = z;  
    
    return Vector3d(new_x, new_y, new_z);
}

std::ostream& operator<<(std::ostream& os, const Vector3d& v)
{
    os << "(" << v.x<< ", " << v.y << ", " << v.z << ")";
    return os;
}

