#pragma once

#include <vector>
#include "Vector3.hpp"
#include <list>

extern double DT;
extern const double G;

class Body {
protected:
    double mass;
private:
    Vector3d pos, vel;
    std::list<Vector3d> trajectory;
    Vector3d last_vel_in_traj;
    std::list<Vector3d> buffer_poses;
public:
    Body() = delete;

    ~Body() = default;

    Body(Vector3d pos_, Vector3d vel_, double mass_);

    const Vector3d &get_pos() const;

    const Vector3d &get_vel() const;

    const double &get_mass() const;

    const std::list<Vector3d> &get_trajectory() const;

    virtual void update_state(const Vector3d &acceleration);

    void update_trajectory();

    Vector3d get_acceleration_without_G(const Vector3d &pos_) const;

};
