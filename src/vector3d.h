#ifndef VECTOR_3D
#define VECTOR_3D

#include <cmath>
#include <iostream>

struct vector3d
{
    // variables
    float x, y, z;

    // inline defined functions
    inline vector3d(void) {}
    inline vector3d(const float x, const float y, const float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline vector3d operator * (float A) const { return vector3d(A*x, A*y, A*z); }

    inline vector3d operator + (const vector3d& A) const { return vector3d(x + A.x, y + A.y, z + A.z); }
    inline vector3d operator - (const vector3d& A) const { return *this + (A*(-1.0)); }

    inline vector3d operator + (float A) const {return vector3d(x + A, y + A, z + A); }
    inline vector3d operator - (float A) const {return *this + (-A); }

    inline float Dot(const vector3d& A)
    {
        return x*A.x + y*A.y + z*A.z;
    }

    // member functions
    float Length();

    // static functions
    static vector3d Max(const vector3d &v, float a)
    {
        return vector3d(
            v.x > a ? v.x : a,
            v.y > a ? v.y : a,
            v.z > a ? v.z : a
        );
    }

    static vector3d Min(const vector3d &v, float a)
    {
        return vector3d(
            v.x < a ? v.x : a,
            v.y < a ? v.y : a,
            v.z < a ? v.z : a
        );
    }

    static vector3d Max(const vector3d& v1, const vector3d& v2)
    {
        return vector3d(
            v1.x > v2.x ? v1.x : v2.x,
            v1.y > v2.y ? v1.y : v2.y,
            v1.z > v2.z ? v1.z : v2.z
        );
    }

    static vector3d Abs(const vector3d& v)
    {
        return vector3d(
            v.x >= 0 ? v.x : -v.x,
            v.y >= 0 ? v.y : -v.y,
            v.z >= 0 ? v.z : -v.z
        );
    }

    // friends (helper functions)
    friend std::ostream& operator <<(std::ostream& os, const vector3d& v);
};


#endif
