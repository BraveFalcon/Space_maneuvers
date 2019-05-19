#include "Jet_Body.h"


Jet_Body::Jet_Body(Vector3d pos_, Vector3d vel_, double own_mass_, double fuel_mass_, double fuel_drain_,
                   double fuel_vel_) : Body(pos_, vel_, own_mass_ + fuel_mass_), fuel_vel(fuel_vel_),
                                       fuel_drain(fuel_drain_),
                                       own_mass(own_mass_), _is_engine_on(false), direction(Vector3d(1, 0, 0)) {}

void Jet_Body::update_state(const Vector3d &acceleration_external) {
    if (_is_engine_on) {
        Body::update_state(fuel_drain * direction * fuel_vel / mass + acceleration_external);
        //mass -= fuel_drain * DT;
        if (mass < own_mass)
            _is_engine_on = false;
    } else
        Body::update_state(acceleration_external);
}

Vector3d Jet_Body::get_direction() const {
    return direction;
}

void Jet_Body::set_direction(Vector3d new_direction) {
    direction = new_direction.normalized();
}

void Jet_Body::engine_on() {
    _is_engine_on = true;
}

void Jet_Body::engine_off() {
    _is_engine_on = false;
}

bool Jet_Body::is_engine_on() const { return _is_engine_on; }
