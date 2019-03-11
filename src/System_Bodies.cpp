#include "System_Bodies.h"


void System_Bodies::append(Body *new_body) {
    bodies_ptrs.push_back(new_body);
}

void System_Bodies::update_state() {
    static std::vector<Vector3d> accelerations_without_G(bodies_ptrs.size());
    for (Vector3d &vec : accelerations_without_G)
        vec.set_values(0.0);
    for (size_t i = 0; i < bodies_ptrs.size() - 1; ++i)
        for (size_t j = i + 1; j < bodies_ptrs.size(); ++j) {
            accelerations_without_G[i] += bodies_ptrs[j]->get_acceleration_without_G(bodies_ptrs[i]->get_pos());
            accelerations_without_G[j] -=
                    accelerations_without_G[i] * bodies_ptrs[i]->get_mass() / bodies_ptrs[j]->get_mass();
        }
    for (size_t i = 0; i < bodies_ptrs.size(); ++i)
        bodies_ptrs[i]->update_state(G * accelerations_without_G[i]);
    time += DT;
}

double System_Bodies::get_time() const {
    return time;
}

Vector3d System_Bodies::get_acceleration(const Vector3d &pos_) const {
    Vector3d res(0.0);
    for (size_t i = 0; i < bodies_ptrs.size(); ++i)
        res += bodies_ptrs[i]->get_acceleration_without_G(pos_);
    return G * res;
}

double System_Bodies::get_full_energy() const {
    double res = 0;
    for (size_t i = 0; i < bodies_ptrs.size(); ++i)
        res += 0.5 * bodies_ptrs[i]->get_mass() * pow(bodies_ptrs[i]->get_vel().abs(), 2);
    for (size_t i = 0; i < bodies_ptrs.size(); ++i)
        for (size_t j = i + 1; j < bodies_ptrs.size(); ++j)
            res -= G * bodies_ptrs[i]->get_mass() * bodies_ptrs[j]->get_mass() /
                   (bodies_ptrs[i]->get_pos() - bodies_ptrs[j]->get_pos()).abs();
    return res;
}

void System_Bodies::update_trajectories() {
    for (Body *body_ptr : bodies_ptrs)
        body_ptr->update_trajectory();
}