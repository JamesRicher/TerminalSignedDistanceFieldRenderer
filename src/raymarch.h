#ifndef RAYMARCH_H
#define RAYMARCH_H

#include "Screen.h"
#include "camera.h"

bool check_pixel(int pixel_index, Screen& screen, Camera& camera, double cur_time);
double scene(vector3d pos, double cur_time);

#endif