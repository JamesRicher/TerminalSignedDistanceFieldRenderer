#ifndef VECTOR_3D
#define VECTOR_3D

#include <cmath>
#include <iostream>

struct Vector3d
{
    // variables
    float x, y, z;

    // inline defined functions
    inline Vector3d(void) {}
    inline Vector3d(const float x, const float y, const float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline Vector3d operator * (float A) const { return Vector3d(A*x, A*y, A*z); }
    inline Vector3d operator * (double A) const { return Vector3d(A*x, A*y, A*z); }

    inline Vector3d operator + (const Vector3d& A) const { return Vector3d(x + A.x, y + A.y, z + A.z); }
    inline Vector3d operator - (const Vector3d& A) const { return *this + (A*(-1.0)); }

    inline Vector3d operator + (float A) const {return Vector3d(x + A, y + A, z + A); }
    inline Vector3d operator - (float A) const {return *this + (-A); }

    inline Vector3d operator % (float A) const { return Vector3d(
        std::fmod(x,A), 
        std::fmod(y,A),
        std::fmod(z,A)); 
    }

    inline float Dot(const Vector3d& A)
    {
        return x*A.x + y*A.y + z*A.z;
    }

    // member functions
    float Length() const;
    Vector3d Normalize() const;

    // static functions
    static Vector3d Max(const Vector3d &v, float a)
    {
        return Vector3d(
            v.x > a ? v.x : a,
            v.y > a ? v.y : a,
            v.z > a ? v.z : a
        );
    }

    static Vector3d Min(const Vector3d &v, float a)
    {
        return Vector3d(
            v.x < a ? v.x : a,
            v.y < a ? v.y : a,
            v.z < a ? v.z : a
        );
    }

    static Vector3d Max(const Vector3d& v1, const Vector3d& v2)
    {
        return Vector3d(
            v1.x > v2.x ? v1.x : v2.x,
            v1.y > v2.y ? v1.y : v2.y,
            v1.z > v2.z ? v1.z : v2.z
        );
    }

    static Vector3d Abs(const Vector3d& v)
    {
        return Vector3d(
            v.x >= 0 ? v.x : -v.x,
            v.y >= 0 ? v.y : -v.y,
            v.z >= 0 ? v.z : -v.z
        );
    }

    // friends (helper functions)
    friend std::ostream& operator <<(std::ostream& os, const Vector3d& v);
};


#endif
