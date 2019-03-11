#pragma once

#include "Planet.hpp"
#include "Animation_System.h"
#include "System_Bodies.h"

double DT = 200;
const double G = 6.67408e-11;

class Solar_System : public Animation_System {
private:
    std::vector<Planet> planets;
    System_Bodies system;
    std::vector<const DrawObject *> draw_objects;
public:
    Solar_System(const std::initializer_list<Planet> &planets_) : planets(planets_.begin(), planets_.end()) {
        for (Planet &planet : planets) {
            system.append(&planet);
            draw_objects.push_back(&planet);
        }
    }

    void update(double time) {
        double start = system.get_time();
        while (system.get_time() - start < time)
            system.update_state();
        system.update_trajectories();
    }

    const std::vector<const DrawObject *> &get_draw_objects() const {
        return draw_objects;
    }

    const Vector3d *get_ptr_pos(size_t i) const {
        return &planets[i].get_pos();
    }

    void keyboard_event(int key, int mode) {};

};