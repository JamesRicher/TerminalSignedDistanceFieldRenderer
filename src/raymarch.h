#ifndef RAYMARCH_H
#define RAYMARCH_H

#include "Screen.h"
#include "camera.h"
#include "vector3d.h"

bool check_pixel(int pixel_index, Screen& screen, Camera& camera);
double scene(vector3d pos);
vector3d get_normal(vector3d pos);

#endif