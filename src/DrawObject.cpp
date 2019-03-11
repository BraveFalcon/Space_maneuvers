#include "DrawObject.h"

void DrawObject::createTexture(const std::string &image_file) {
    GLint tex_width, tex_height;
    unsigned char *image = SOIL_load_image(image_file.c_str(), &tex_width, &tex_height, nullptr, SOIL_LOAD_RGBA);
    if (!image)
        std::cerr << "Can't load texture:" << image_file << std::endl, exit(1);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image);

}

void DrawObject::activateTexture() const {
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void DrawObject::deactivateTexture() const {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
}
