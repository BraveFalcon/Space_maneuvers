#pragma once

#include "Planet.hpp"
#include "Rocket.hpp"
#include "Animation_System.h"
#include "System_Bodies.h"
#include <SFML/Graphics.hpp>

double DT = 200;
const double G = 6.67408e-11;

class Solar_System : public Animation_System {
private:
    std::vector<Planet> planets;
    Rocket rocket;
    System_Bodies system;
    std::vector<const sf::Drawable *> draw_objects;
public:
    Solar_System(Rocket &&rocket_, const std::initializer_list<Planet> &planets_) : rocket(rocket_),
                                                                                    planets(planets_) {
        draw_objects.push_back(&rocket);
        for (Planet &planet : planets) {
            system.append(&planet);
            draw_objects.push_back(&planet);
        }
    }

//    Solar_System(std::vector<Planet> &&planets_) : planets{std::move(planets_)} {
//        for (Planet &planet : planets) {
//            system.append(&planet);
//            draw_objects.push_back(&planet);
//        }
//    }

    void update(double time) final {
        double start = system.get_time();
        while (system.get_time() - start < time) {
            system.update_state();
            rocket.update_state(system.get_acceleration(rocket.get_pos()));
        }
        rocket.sprite.setPosition(static_cast<float>(rocket.get_pos().x), static_cast<float>(rocket.get_pos().y));
        for (auto &planet : planets)
            planet.sprite.setPosition(static_cast<float>(planet.get_pos().x), static_cast<float>(planet.get_pos().y));
        static double last_review_time;
        bool review = system.get_time() - last_review_time > 365 * 24 * 3600;
        if (review)
            last_review_time = system.get_time();
        rocket.update_trajectory(review);
        for (auto &planet : planets)
            planet.update_trajectory(review);
    }

    const std::vector<const sf::Drawable *> &get_draw_objects() const final {
        return draw_objects;
    }

    const Vector3d *get_ptr_pos(size_t i) const final {
        if (i < planets.size())
            return &(planets[i].get_pos());
        else
            return &(rocket.get_pos());
    }

    void keyboard_event(sf::Event event) final {
        using sf::Keyboard;
        switch (event.key.code) {
            case Keyboard::Space:
                rocket.switch_engine();
                break;
            default:
                break;
        }
    };

    void keyboard_handler(const float fps) final {
        float delta_angle = 60 / fps;
        using sf::Keyboard;
        if (Keyboard::isKeyPressed(Keyboard::Q))
            rocket.rotate(delta_angle);
        if (Keyboard::isKeyPressed(Keyboard::E))
            rocket.rotate(-delta_angle);
    }

};