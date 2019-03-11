#pragma once

#include "Body.h"
#include "Vector3.hpp"
#include "DrawObject.h"
#include <GL/glut.h>
#include "Color.hpp"

class Planet : public Body, public DrawObject {
private:
    Color color;
public:
    Planet() = delete;

    Planet(Vector3d pos_, Vector3d vel_, double mass_, Color color_, const std::string &image_file) :
            Body(pos_, vel_, mass_), color(color_) {
        createTexture(image_file);
    }

    void draw(double scale) const {
        glPointSize(20);
        glColor3fv(color.get_ptr());

        glBegin(GL_POINTS);
        glVertex3d(get_pos().x, get_pos().y, 0);
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (const Vector3d &pos : get_trajectory())
            glVertex3d(pos.x, pos.y, 0);
        glEnd();
    }
};