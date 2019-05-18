#pragma once

#include "Planet.hpp"
#include "Animation_System.h"
#include "System_Bodies.h"
#include <SFML/Graphics.hpp>

double DT = 200;
const double G = 6.67408e-11;

class Solar_System : public Animation_System {
private:
    std::vector<Planet> planets;
    System_Bodies system;
    std::vector<const sf::Drawable *> draw_objects;
public:
    Solar_System(const std::initializer_list<Planet> &planets_) {
        for (const auto &planet : planets_)
            planets.push_back(planet);
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
        while (system.get_time() - start < time)
            system.update_state();
        system.update_trajectories();
        for (auto &planet : planets)
            planet.sprite.setPosition(static_cast<float>(planet.get_pos().x), static_cast<float>(planet.get_pos().y));

    }

    const std::vector<const sf::Drawable *> &get_draw_objects() const final {
        return draw_objects;
    }

    const Vector3d *get_ptr_pos(size_t i) const final {
        return &(planets[i].get_pos());
    }

    void keyboard_event(int key, int mode) final {};

};