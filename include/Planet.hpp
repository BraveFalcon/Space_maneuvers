#pragma once

#include "Body.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

extern const float INIT_VIEW_SIZE;

class Solar_System;

class Planet : public Body, public sf::Drawable {
private:
    sf::Color color;
    sf::Texture texture;
    sf::Sprite sprite;
    friend Solar_System;
    float radius;
    float view_scale;
    static constexpr float init_view_size = 0.2e8;
public:

    Planet() = delete;

    Planet(const Planet &planet) : Body(planet), color(planet.color),
                                   texture(planet.texture), sprite(planet.sprite), radius(planet.radius),
                                   view_scale(planet.view_scale) {
        sprite.setTexture(texture);
    }

    Planet(Vector3d pos_, Vector3d vel_, double mass_, float radius_, sf::Color color_, float view_scale_,
           const std::string &image_file) :
            Body(pos_, vel_, mass_), color(color_), radius(radius_), view_scale(view_scale_) {
        if (!texture.loadFromFile(image_file))
            exit(1);
        sprite.setTexture(texture);
        sprite.setScale(sf::Vector2f(init_view_size, init_view_size) * view_scale);
        sprite.setOrigin(texture.getSize().x * 0.5f, texture.getSize().y * 0.5f);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const final {
        //Костыль
        target.pushGLStates();
        glLineWidth(4);
        glColor3ub(color.r, color.g, color.b);

        glBegin(GL_LINE_STRIP);
        for (const Vector3d &pos : get_trajectory())
            glVertex2d(pos.x, -pos.y); //revert y-axis
        glEnd();
        //std::cout << get_trajectory().size() << '\n';

        target.popGLStates();

        //std::cout << states.transform.
        states.transform.scale(1, -1); //revert y-axis
        sf::Sprite cur_sprite(sprite);
        if (target.getView().getSize().x < INIT_VIEW_SIZE) {
            cur_sprite.scale(sf::Vector2f(1, 1) * (target.getView().getSize().x / INIT_VIEW_SIZE));
            if (1024 * init_view_size * view_scale * target.getView().getSize().x / INIT_VIEW_SIZE < radius) {
                cur_sprite.scale(sf::Vector2f(1, 1) *
                                 (radius / (1024 * init_view_size * view_scale * target.getView().getSize().x /
                                            INIT_VIEW_SIZE)));

                std::cout << radius / (1024 * init_view_size * view_scale * target.getView().getSize().x /
                                       INIT_VIEW_SIZE) << std::endl;
            }
        }
        if (color == sf::Color::Yellow) {
            //std::cout << 1024 * init_view_size * view_scale * target.getView().getSize().x / INIT_VIEW_SIZE << '\n';
            //std::cout << radius << '\n';
        }

        target.draw(cur_sprite, states);
    }
};