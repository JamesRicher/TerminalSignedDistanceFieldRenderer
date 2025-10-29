#ifndef CONSTANTS
#define CONSTANTS

#include <chrono>

const float PI = 3.14159265359;
const int FPS = 30;
const double FRAME_TIME = 1.0/FPS;

const auto START_TIME = std::chrono::high_resolution_clock::now();

const double DEG_TO_RAD = 180.0/PI;

// authored constants options
const int HEIGHT = 70;
const double ASPECT = 1.0; // final aspect ratio of the image
const double HALF_FOV_DEG_X = 45.0; // camera horizontal fov

#endif
