#pragma once

#include "Vector3.hpp"
#include "Body.h"

class System_Bodies {
private:
    std::vector<Body *> bodies_ptrs;
    double time = 0;
public:

    System_Bodies() = default;

    ~System_Bodies() = default;

    void append(Body *new_body);

    void update_state();

    double get_time() const;

    Vector3d get_acceleration(const Vector3d &pos_) const;

    double get_full_energy() const;
};

