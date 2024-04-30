// sphere.h
#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>

class Sphere {
public:
    GLuint textureID; // Texture ID
    GLfloat radius;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat density;
    GLfloat mass;
    GLfloat vx;
    GLfloat vy;
    GLfloat vz;
    
    Sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLfloat density);
    void draw(GLint slices, GLint stacks);
};

#endif // SPHERE_H