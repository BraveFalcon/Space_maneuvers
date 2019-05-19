#pragma once

#include "Jet_Body.h"
#include "SFML/Graphics.hpp"
#include "Vector3.hpp"
#include <SFML/OpenGL.hpp>
#include "Planet.hpp"

class Solar_System;

class Rocket : public Jet_Body, public sf::Drawable {
private:
    sf::Color color;
    sf::Texture texture_off;
    sf::Texture texture_on;
    sf::Sprite sprite;
    friend Solar_System;
public:
    Rocket() = delete;

    Rocket(const Rocket &rocket) : Jet_Body(rocket), color(rocket.color), texture_off(rocket.texture_off),
                                   texture_on(rocket.texture_on), sprite(rocket.sprite) {
        sprite.setTexture(texture_off);
    }

    Rocket(Vector3d pos_, Vector3d vel_, double own_mass_, double fuel_mass_, double fuel_drain_, double fuel_vel_,
           sf::Color color_, const std::string &image_engine_off, const std::string &image_engine_on) : Jet_Body(pos_,
                                                                                                                 vel_,
                                                                                                                 own_mass_,
                                                                                                                 fuel_mass_,
                                                                                                                 fuel_drain_,
                                                                                                                 fuel_vel_),
                                                                                                        color(color_) {
        if (!texture_off.loadFromFile(image_engine_off) || !texture_on.loadFromFile(image_engine_on))
            exit(1);
        sprite.setTexture(texture_off);
        sprite.setScale(0.2e8, 0.2e8);
        sprite.setOrigin(texture_off.getSize().x * 0.5f, texture_off.getSize().y * 0.5f);
        sprite.setRotation(90);
    }

//TODO::repair it
    void switch_engine() {
        if (is_engine_on()) {
            engine_off();
            sprite.setTexture(texture_off);
        } else {
            engine_on();
            sprite.setTexture(texture_on);
        }
    }

    void rotate(float angle_deg) {
        sprite.rotate(angle_deg);
        double angle = angle_deg / 180.0 * M_PI;
        double x = get_direction().x;
        double y = get_direction().y;
        double cos = std::cos(angle);
        double sin = std::sin(angle);
        std::cout << get_direction() << '\t' << angle << '\t';
        set_direction(Vector3d(x * cos - y * sin, x * sin + y * cos, 0));
        std::cout << get_direction() << "\n";
    }

//TODO::Learn more about combining SFML and OpenGL
    void draw(sf::RenderTarget &target, sf::RenderStates states) const final {
        //Костыль
        target.draw(sf::CircleShape());
        target.pushGLStates();
        glLineWidth(4);
        glColor3ub(color.r, color.g, color.b);

        glBegin(GL_LINE_STRIP);
        for (const Vector3d &pos : get_trajectory())
            glVertex2d(pos.x, -pos.y); //revert y-axis
        glEnd();
        //std::cout << get_trajectory().size() << '\n';

        target.popGLStates();

        states.transform.scale(1, -1); //revert y-axis
        target.draw(sprite, states);
    }
};