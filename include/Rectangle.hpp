#pragma once

#include "DrawObject.h"
#include "Vector3.hpp"

class Rectangle : public DrawObject {
private:
    double x_left;
    double x_right;
    double y_bottom;
    double y_top;
public:
    Rectangle() = default;

    Rectangle(double x_left, double y_bottom, double x_right, double y_top, const std::string &image_file) : x_left(x_left), x_right(x_right),
                                                                              y_bottom(y_bottom), y_top(y_top) {
        createTexture(image_file);
    }

    Rectangle(Vector3d center, double r) : x_left(center.x - r), x_right(center.x + r),
                                           y_bottom(center.y - r), y_top(center.y + r) {}

    void draw(double scale) const {
        activateTexture();
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0), glVertex2d(x_left, y_bottom);
        glTexCoord2f(0.0, 1.0), glVertex2d(x_left, y_top);
        glTexCoord2f(1.0, 1.0), glVertex2d(x_right, y_top);
        glTexCoord2f(1.0, 0.0), glVertex2d(x_right, y_bottom);
        glEnd();
        deactivateTexture();
    }
};