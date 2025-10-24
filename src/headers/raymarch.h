#ifndef RAYMARCH_H
#define RAYMARCH_H

#include "Screen.h"
#include "Camera.h"
#include "Vector3d.h"

char check_pixel(int pixel_index, Screen& screen, Camera& camera);
double scene(Vector3d pos);
Vector3d get_normal(Vector3d pos);

#endif
