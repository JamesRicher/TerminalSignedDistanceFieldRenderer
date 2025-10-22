#ifndef CONSTANTS
#define CONSTANTS

#include <chrono>

const float PI = 3.14159265359;
const int FPS = 48;
const double FRAME_TIME = 1.0/FPS;

// raymarching settings
const int MAX_STEPS = 100;
const double MAX_DIST = 1000.0;
const double EPS = 0.01; // defines what counts as a hit

const double CHAR_ASPECT = 2.0; // aspect ratio of a character printed on the terminal

const auto START_TIME = std::chrono::high_resolution_clock::now();

#endif
