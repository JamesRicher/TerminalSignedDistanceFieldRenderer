#ifndef RAYMARCH_H
#define RAYMARCH_H

#include "Screen.h"
#include "Camera.h"
#include "Vector3d.h"

class Raymarcher
{
private:
    Camera* cam;
    Screen* screen;

public:
    // constructors
    Raymarcher(Camera* cam, Screen* screen);

};

bool check_pixel(int pixel_index, Screen& screen, Camera& camera, Vector3d& normal);
double scene(Vector3d pos);
Vector3d get_normal(Vector3d pos);

#endif
