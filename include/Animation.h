#pragma once

#include <time.h>
#include "Vector3.hpp"
#include <GL/glut.h>
#include "Animation_System.h"
#include "Color.hpp"
#include "Rectangle.hpp"

class Animation{
private:
    static Animation *instance_wrap;

    Animation_System *anim_sys;
    Rectangle background;

    const int window_width = 1920, window_height = 1080;

    double_t init_anim_speed = 10000;
    double_t anim_speed = init_anim_speed;

    const double init_scale = window_height / 500e9;
    double scale = init_scale;

    const Vector3d *pos_center = new Vector3d(0);
    double x_shift = 0, y_shift = 0;

    int window;

    void keyboard_event(unsigned char key, int x, int y);

    static void keyboard_event_wrap(unsigned char key, int x, int y);

    void spec_keyboard_event(int key, int x, int y);

    static void spec_keyboard_event_wrap(int key, int x, int y);

    void display();

    static void display_wrap();

public:
    Animation(Animation_System *animation_system, const std::string &background_image);

    void run();
};