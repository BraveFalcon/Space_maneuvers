#include <Vector3.hpp>
#include "Body.h"

Body::Body(Vector3d pos_, Vector3d vel_, double mass_) : mass(mass_), pos(pos_), vel(vel_), last_vel_in_traj(vel_) {
    trajectory.push_back(pos_);
}

const Vector3d &Body::get_pos() const{ return pos; }

const Vector3d &Body::get_vel() const{ return vel; }

const double &Body::get_mass() const{ return mass; }

void Body::update_state(const Vector3d &acceleration) {
    vel += acceleration * DT;
    pos += vel * DT;
    buffer_poses.push_back(pos);
}

void Body::update_trajectory() {
    const double max_angle = 3 / 180. * M_PI;
    const double min_cos = cos(max_angle);

    for (const auto &new_pos : buffer_poses){
        Vector3d new_line = new_pos - trajectory.back();
        double new_angle_cos = new_line.dot(last_vel_in_traj) / new_line.abs() / last_vel_in_traj.abs();
        if (new_angle_cos < min_cos)
            trajectory.push_back(new_pos);
    }

    if (trajectory.back() != buffer_poses.back())
        trajectory.push_back(buffer_poses.back());

    buffer_poses.clear();
    last_vel_in_traj = vel;
}

Vector3d Body::get_acceleration_without_G(const Vector3d &pos_) const{
    const Vector3d r = pos - pos_;
    return mass * r.normalized() / r.sqr();
}

const std::list<Vector3d> &Body::get_trajectory()const {
    return trajectory;
}
