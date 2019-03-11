#include <GL/glut.h>
#pragma once
struct Color {
private:
    GLfloat comp[3];
public:
    Color(int red = 0, int green = 0, int blue = 0){
        comp[0] = red / (GLfloat) 255;
        comp[1] = green / (GLfloat) 255;
        comp[2] = blue / (GLfloat) 255;
    }

    const GLfloat *get_ptr() const{
        return comp;
    }
};