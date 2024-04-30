// texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL/SOIL.h>
#include <GL/glut.h>
#include <iostream>
#include "sphere.h"

void loadTexture(const char* filename, GLuint &objectTexture) {
    objectTexture = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (!objectTexture) {
        std::cerr << "Error loading texture: " << SOIL_last_result() << std::endl;
    }
}

void draw_texturedobject(GLuint objectTexture, Sphere object, GLint slices, GLint stacks) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objectTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    object.draw(slices, stacks);
    glDisable(GL_TEXTURE_2D);
}

void draw_texturedobject_inner(GLuint objectTexture, Sphere object, GLint slices, GLint stacks) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objectTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    object.draw_inner(slices, stacks);
    glDisable(GL_TEXTURE_2D);
}



#endif // TEXTURE_H