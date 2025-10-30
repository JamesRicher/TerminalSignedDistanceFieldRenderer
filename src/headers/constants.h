#ifndef CONSTANTS
#define CONSTANTS

#include <chrono>

const float PI = 3.14159265359;
const int FPS = 30;
const double FRAME_TIME = 1.0/FPS;

const auto START_TIME = std::chrono::high_resolution_clock::now();

const double DEG_TO_RAD = 180.0/PI;

#endif
