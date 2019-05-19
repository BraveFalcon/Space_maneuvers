#pragma once

#include "Body.h"

class Jet_Body : public Body {
private:
    double fuel_vel;
    double fuel_drain;
    const double own_mass;
    Vector3d direction;
    bool _is_engine_on;
public:
    Jet_Body() = delete;

    ~Jet_Body() = default;

    Jet_Body(Vector3d pos_, Vector3d vel_, double own_mass_, double fuel_mass_, double fuel_drain_,
             double fuel_vel_);

    void update_state(const Vector3d &acceleration_external) final;

    Vector3d get_direction() const;

    void set_direction(Vector3d new_direction);

    void engine_on();

    void engine_off();

    bool is_engine_on() const;
};

