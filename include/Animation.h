#pragma once

#include <time.h>
#include "Vector3.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Animation_System.h"


class Animation {
private:
    unsigned long frame = 0;
    sf::Texture _background_texture;
    sf::Sprite background;
    Animation_System *animation_system;

    bool is_run = true;
    double_t init_anim_speed = 10 * 24 * 3600;
    double_t anim_speed = init_anim_speed;


    const Vector3d *pos_center = new Vector3d(0);
    float x_shift = 0, y_shift = 0;

    sf::RenderWindow window;

    const float init_scale;
    float scale;

    void keyboard_handler(float fps);

    void keyboard_event(sf::Event event);

    void draw();

    int get_fps();

    sf::Font _monospacedFont;
    sf::Text fps_text;

public:
    explicit Animation(Animation_System *animationSystem);

    void set_background(const std::string &image_file);

    void run();
};