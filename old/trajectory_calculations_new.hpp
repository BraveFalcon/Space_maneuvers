/*
#include <vector>
#include "Vector3.hpp"

double DT = 20;
const double G = 6.67408e-11;

class Body {
protected:
    double mass;
private:
    Vector3d pos, vel;
public:
    Body() = default;

    ~Body() = default;

    Body(Vector3d pos_, Vector3d vel_, double mass_) : mass(mass_), pos(pos_), vel(vel_) {}

    Vector3d get_pos() { return pos; }

    Vector3d get_vel() { return vel; }

    double get_mass() { return mass; }

    void update_state(const Vector3d &acceleration) {
        vel += acceleration * DT;
        pos += vel * DT;
    }

    Vector3d get_acceleration_without_G(const Vector3d &pos_) {
        const double r_abs = (pos - pos_).abs();
        return mass * (pos - pos_) / (r_abs * r_abs * r_abs);
    }
};

class Jet_Body : public Body {
private:
    double fuel_vel;
    double fuel_drain;
    const double own_mass;
public:
    Jet_Body() = delete;

    ~Jet_Body() = default;

    Jet_Body(Vector3d pos_, Vector3d vel_, double own_mass_, double fuel_mass_, double fuel_drain_,
           double fuel_vel_) : Body(pos_, vel_, own_mass_ + fuel_mass_), fuel_vel(fuel_vel_), fuel_drain(fuel_drain_),
                               own_mass(own_mass_) {}

    void update_state(const Vector3d &acceleration_external, Vector3d direction_thrust) {
        if (mass > own_mass) {
            direction_thrust /= direction_thrust.abs();
            Body::update_state(fuel_drain * direction_thrust * fuel_vel / mass + acceleration_external);
            mass -= fuel_drain * DT;
        } else {
            Body::update_state(acceleration_external);
        }
    }
};

class System_Planets {
private:
    std::vector<Body> planets;
    const size_t sssize;
    double time = 0;
public:

    System_Planets() = default;

    ~System_Planets() = default;

    void append(const Body &new_body) {
        planets.push_back(new_body);
    }

    Body &operator[](size_t i) {
        return planets[i];
    };

    void update_state() {
        static std::vector<Vector3d> accelerations_without_G(sssize);
        for (Vector3d &vec : accelerations_without_G)
            vec.set_values(0.0);
        for (size_t i = 0; i < sssize - 1; ++i)
            for (size_t j = i + 1; j < sssize; ++j) {
                accelerations_without_G[i] += planets[j].get_acceleration_without_G(planets[i].get_pos());
                accelerations_without_G[j] -=
                        accelerations_without_G[i] * planets[i].get_mass() / planets[j].get_mass();
            }
        for (size_t i = 0; i < sssize; ++i)
            planets[i].update_state(G * accelerations_without_G[i]);
        time += DT;
    }

    double get_time(){
        return time;
    }

    Vector3d get_acceleration(const Vector3d &pos_) {
        Vector3d res(0.0);
        for (size_t i = 0; i < sssize; ++i)
            res += planets[i].get_acceleration_without_G(pos_);
        return G * res;
    }

    double get_full_energy() {
        double res = 0;
        for (size_t i = 0; i < sssize; ++i)
            res += 0.5 * planets[i].get_mass() * pow(planets[i].get_vel().abs(), 2);
        for (size_t i = 0; i < sssize; ++i)
            for (size_t j = i + 1; j < sssize; ++j)
                res -= G * planets[i].get_mass() * planets[j].get_mass() /
                       (planets[i].get_pos() - planets[j].get_pos()).abs();
        return res;
    }
};
 */