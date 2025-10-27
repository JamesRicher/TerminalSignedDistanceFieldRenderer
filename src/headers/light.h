#ifndef LIGHT_H 
#define LIGHT_H

#include "Vector3d.h"

class Light
{
private:
    Vector3d direction;
    double strength;

public:
    // constructors 
    Light(Vector3d direction, double strength);

    double calculate_diffuse(Vector3d normal);
};

#endif
