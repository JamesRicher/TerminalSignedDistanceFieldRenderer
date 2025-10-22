#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

class Screen
{
private:
    const char EMPTY_CHAR = ' ';

    int width;
    int height;
    int pixels;
    double half_pixel_width; // in NDC space
    double half_pixel_height; //in NDC space
    std::vector<char> pixels_vector;
public:
    Screen(int height, double asepct);
    void print();
    void clear();
    bool set_pixel(int pixel_index, char c);
    int get_pixel_count();
    void pi_to_ndc(int pi, double& ndc_x, double& ndc_y) const;

    static void clear_terminal();
    static void hide_cursor();
    static void unhide_cursor();
};

#endif
