#ifndef SDF
#define SDF

#include "Vector3d.h"

float sdf_sphere(Vector3d pos, float radius);
float sdf_box(Vector3d pos, Vector3d box);

double op_union(double d1, double d2);
double op_intersection(double d1, double d2);
double op_subtraction(double d1, double d2);
double op_xor(double d1, double d2);

double op_smooth_union(double d1, double d2, double k);
double op_smooth_intersection(double d1, double d2, double k);
double op_smooth_subtraction(double d1, double d2, double k);

#endif
