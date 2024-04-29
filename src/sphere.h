// sphere.h
#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>

class Sphere {
public:
    GLuint textureID; // Texture ID

    Sphere(const char* filename);
    void draw(GLfloat radius, GLint slices, GLint stacks, GLfloat x, GLfloat y, GLfloat z);
};

#endif // SPHERE_H