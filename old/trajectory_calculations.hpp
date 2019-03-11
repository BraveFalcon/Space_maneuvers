#include "Vector3.hpp"


double DT = 20;
const double G = 6.67408e-11;

struct Body {
private:
    double dp; //u * dm --- испульс топлива
    double dm;
public:
    Vector3d pos, vel;
    double mass;
    double own_mass;


    Body() = default;

    ~Body() = default;

    Body(Vector3d pos_, Vector3d vel_, double mass_) {
        mass = mass_;
        pos = pos_;
        vel = vel_;
    }

    Body(Vector3d pos_, Vector3d vel_, double own_mass_, double fuel_mass_, double fuel_output_,
         double fuel_vel_) {
        mass = own_mass_ + fuel_mass_;
        own_mass = own_mass_;
        dm = fuel_output_ * DT;
        dp = fuel_vel_ * dm;
        pos = pos_;
        vel = vel_;
    }

    void update_state(const Vector3d &acceleration) {
        vel += acceleration * DT;
        pos += vel * DT;
    }

    void update_state(const Vector3d &acceleration_external, const Vector3d &direction_thrust) {
        vel += direction_thrust * dp / mass + acceleration_external * DT;
        pos += vel * DT;
        mass -= dm;
    }

    Vector3d get_acceleration_without_G(const Vector3d &pos_) {
        const double r_abs = (pos - pos_).abs();
        return mass * (pos - pos_) / (r_abs * r_abs * r_abs);
    }
};

struct System_Planets {
private:
    Vector3d *accelerations_without_G;
    Body *planets;
public:
    size_t size;

    System_Planets(std::initializer_list<Body> planets_) {
        size = planets_.size();
        planets = (Body *) malloc(size * sizeof(Body));
        accelerations_without_G = (Vector3d *) malloc(size * sizeof(Vector3d));
        size_t i = 0;
        for (const Body &planet_ : planets_) {
            accelerations_without_G[i] = Vector3d(0.0);
            planets[i++] = planet_;
        }
    }

    ~System_Planets() {
        free(planets);
        free(accelerations_without_G);
    }

    Body &operator[](size_t i) {
        return planets[i];
    };

    void update_state() {
        for (size_t i = 0; i < size - 1; ++i)
            for (size_t j = i + 1; j < size; ++j) {
                accelerations_without_G[i] += planets[j].get_acceleration_without_G(planets[i].pos);
                accelerations_without_G[j] -= accelerations_without_G[i] * planets[i].mass / planets[j].mass;
            }
        for (size_t i = 0; i < size; ++i) {
            planets[i].update_state(G * accelerations_without_G[i]);
            accelerations_without_G[i].set_values(0.0);
        }
    }

    Vector3d get_acceleration(const Vector3d &pos_) {
        Vector3d res(0.0);
        for (size_t i = 0; i < size; ++i)
            res += planets[i].get_acceleration_without_G(pos_);
        return G * res;
    }

    double get_full_energy() {
        double res = 0;
        for (size_t i = 0; i < size; ++i)
            res += 0.5 * planets[i].mass * pow(planets[i].vel.abs(), 2);
        for (size_t i = 0; i < size; ++i)
            for (size_t j = i + 1; j < size; ++j)
                res -= G * planets[i].mass * planets[j].mass / (planets[i].pos - planets[j].pos).abs();
        return res;
    }
};

