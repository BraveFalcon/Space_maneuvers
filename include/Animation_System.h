#pragma once

#include "DrawObject.h"
#include "vector"
#include "Vector3.hpp"
#include <GL/glut.h>

class Animation_System{
public:
    virtual void update(double time) = 0;

    virtual const std::vector<const DrawObject *> &get_draw_objects() const = 0;

    virtual const Vector3d *get_ptr_pos(size_t i) const = 0;

    virtual void keyboard_event(int key, int mode) = 0;

};
