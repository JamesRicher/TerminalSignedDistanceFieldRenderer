#ifndef SDF
#define SDF

#include "vector3d.h"

float sdf_sphere(vector3d pos, float radius, vector3d centre);
float sdf_box(vector3d pos, vector3d box);

#endif
