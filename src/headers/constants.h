#ifndef CONSTANTS
#define CONSTANTS

#include <chrono>

const float PI = 3.14159265359;
const int FPS = 50;
const double FRAME_TIME = 1.0/FPS;

// raymarching settings
const int MAX_STEPS = 200;
const double MAX_DIST = 1000.0;
const double EPS = 0.001; // defines what counts as a hit

const auto START_TIME = std::chrono::high_resolution_clock::now();

// authored constants options
const int HEIGHT = 50;
const double ASPECT = 1.5; // final aspect ratio of the image
const double HALF_FOV_DEG_X = 45.0; // camera horizontal fov

#endif
