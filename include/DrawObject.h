#pragma once

#include <iostream>
#include <GL/glut.h>
#include <string>
#include <SOIL/SOIL.h>

class DrawObject {
private:
    GLuint texture;
public:
    void createTexture(const std::string &image_file);

    void activateTexture() const;

    void deactivateTexture() const;

    virtual void draw(double scale) const = 0;
};