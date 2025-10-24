#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

class Screen
{
private:
    const char EMPTY_CHAR = ' ';
    const double CHAR_ASPECT = 2.0;

    // the width and height of the screen in pixels
    int width;
    int height;
    int pixels;

    // the aspect ratio of the screen accounting for the aspect ratio of a character 
    double aspect;

    // the distance from a pixel corner to its centre
    double half_pixel_width; // in NDC space
    double half_pixel_height; //in NDC space
    
    // the actual character representation of the screen
    std::vector<char> pixels_vector;

public:
    // constructors
    Screen(int height, double asepct);
    Screen();

    // output the screen to the terminal
    void print();
    // sets each entry in screen to EMPTY_CHAR
    void clear();
    // sets the value of a pixel at a given pixel
    bool set_pixel(int pixel_index, char c);
    void pi_to_ndc(int pi, double& ndc_x, double& ndc_y) const;

    // getters
    inline int get_pixel_count() const { return pixels; }
    inline double get_aspect() const { return aspect; }
    inline char get_empty_char() const { return EMPTY_CHAR; }

    // static methods
    static void clear_terminal();
    static void hide_cursor();
    static void unhide_cursor();
};

#endif
