#include "Camera.h"
#include "Screen.h"
#include "Vector3d.h"
#include "graphics_context.h"

GraphicsContext::GraphicsContext(int screen_height, double aspect,
                                 double half_fov_x, Vector3d cam_pos,
                                 int steps, double dist, double eps)
    :   cam(half_fov_x, aspect, cam_pos),
        screen(screen_height, aspect),
        raymarcher(steps, dist, eps)
{

}

void GraphicsContext::draw_frame()
{
    screen.clear_buffer();

    for (int i=0; i < screen.get_pixel_count(); i++)
    {
        Vector3d normal;
        double ndc_x, ndc_y;
        screen.pi_to_ndc(i, ndc_x, ndc_y);
        Vector3d pixel_wpos = cam.ndc_to_world_pos(ndc_x, ndc_y);
        bool hit = raymarcher.raymarch(cam.pos, pixel_wpos, normal); 

        if (hit)
        {
            screen.set_pixel(i,1);
        }   
    }

    Screen::clear_terminal();
    screen.print();
}

GraphicsContext::~GraphicsContext()
{
}   
