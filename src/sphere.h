// sphere.h
#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Sphere {
public:
    GLuint textureID; // Texture ID
    GLfloat radius;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat mass;
    GLfloat vx;
    GLfloat vy;
    GLfloat vz;
    GLfloat ax;
    GLfloat ay;
    GLfloat az;
    vector<GLfloat> tracePoints;
   
    Sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLfloat mass);
    void set_kinematics(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat ax, GLfloat ay, GLfloat az);
    void draw(GLint slices, GLint stacks);
    void draw_inner(GLint slices, GLint stacks);
    void update_position(vector<Sphere*>& spheres);
    void draw_trace();
};

#endif // SPHERE_H