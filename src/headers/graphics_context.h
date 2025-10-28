#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include "Camera.h"
#include "Screen.h"
#include "Vector3d.h"
#include "raymarch.h"

class GraphicsContext
{
private:
    Camera cam;
    Screen screen;
    Raymarcher raymarcher;

public:
    //constructor
    GraphicsContext(int screen_height, double aspect, 
                    double half_fov_x, Vector3d cam_pos,
                    int steps, double dist, double eps);

    void draw_frame();
    //destructor
    ~GraphicsContext();
};

#endif
