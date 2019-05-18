#pragma once

#include "Body.h"
#include "Vector3.hpp"
#include "Color.hpp"
#include <SFML/Graphics.hpp>

class Solar_System;

class Planet : public Body, public sf::Drawable {
private:
    sf::Color color;
    sf::Texture texture;
    sf::Sprite sprite;
    friend Solar_System;
public:

    Planet() = delete;

    Planet(const Planet &planet) : Body(planet.get_pos(), planet.get_vel(), planet.get_mass()), color(planet.color),
                                   texture(planet.texture), sprite(planet.sprite) {
        sprite.setTexture(texture);
    }
    //Planet(Planet &&p) = default;

    Planet(Vector3d pos_, Vector3d vel_, double mass_, sf::Color color_, const std::string &image_file) :
            Body(pos_, vel_, mass_), color(color_) {
        if (!texture.loadFromFile(image_file))
            exit(1);
        sprite.setTexture(texture);
        sprite.setScale(0.2e8, 0.2e8);
        sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const final {
        target.pushGLStates();
        glLineWidth(9);
        glColor3ub(color.r, color.g, color.b);

        glBegin(GL_LINE_STRIP);
        for (const Vector3d &pos : get_trajectory())
            glVertex2d(pos.x, pos.y);
        glEnd();

        target.popGLStates();

        target.resetGLStates();
        target.draw(sprite, states);
    }
};