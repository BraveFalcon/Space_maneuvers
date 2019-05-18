#pragma once

#include "vector"
#include "Vector3.hpp"
#include <SFML/Graphics.hpp>

class Animation_System{
public:
    virtual void update(double time) = 0;

    virtual const std::vector<const sf::Drawable *> &get_draw_objects() const = 0;

    virtual const Vector3d *get_ptr_pos(size_t i) const = 0;

    virtual void keyboard_event(sf::Event event) = 0;

};
