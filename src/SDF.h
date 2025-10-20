#ifndef SDF
#define SDF

#include "vector3d.h"

float sdf_sphere(vector3d pos, float radius, vector3d centre);
float sdf_box(vector3d pos, vector3d box);

double op_union(double d1, double d2);
double op_intersection(double d1, double d2);
double op_subtraction(double d1, double d2);
double op_xor(double d1, double d2);

double op_smooth_union(double d1, double d2, double k);
double op_smooth_intersection(double d1, double d2, double k);
double op_smooth_subtraction(double d1, double d2, double k);

#endif
