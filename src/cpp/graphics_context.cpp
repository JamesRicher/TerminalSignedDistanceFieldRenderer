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
    lights.push_back(Light(Vector3d(1,1,1),1.0));
}

void GraphicsContext::draw_frame()
{
    screen.clear_buffer();

    for (int i=0; i < screen.get_pixel_count(); i++)
    {
        Vector3d normal;
        double ndc_x, ndc_y;
        screen.pi_to_ndc(i,ndc_x,ndc_y);

        Vector3d pixel_wpos = cam.ndc_to_world_pos(ndc_x, ndc_y);
        bool hit = raymarcher.raymarch(cam.pos, pixel_wpos, normal); 

        if (hit)
        {
            double light = get_normalised_light(normal);
            screen.set_pixel(i,light);
        }   
    }

    Screen::clear_terminal();
    screen.print_buffer();
}

double GraphicsContext::get_normalised_light(const Vector3d& normal)
{
    double light = 0;
    for (Light l : lights)
    {
        light += l.calculate_diffuse(normal);
    }
    return light;
}

GraphicsContext::~GraphicsContext()
{
}   
