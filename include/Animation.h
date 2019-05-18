#pragma once

#include <time.h>
#include "Vector3.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Animation_System.h"
#include "Color.hpp"

class Animation {
private:
    sf::Texture _background_texture;
    sf::Sprite background;
    Animation_System *animation_system;

    double_t init_anim_speed = 10000;
    double_t anim_speed = init_anim_speed;



    const Vector3d *pos_center = new Vector3d(0);
    double x_shift = 0, y_shift = 0;

    sf::RenderWindow window;

    const double init_scale;

    sf::View view;


    void keyboard_handler();

    void draw();


public:
    explicit Animation(Animation_System *animationSystem);

    void set_background(const std::string &image_file);

    void run();
};