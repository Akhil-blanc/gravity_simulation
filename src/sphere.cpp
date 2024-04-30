// sphere.cpp
#include "sphere.h"

Sphere::Sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLfloat density) {

    this->radius = radius;
    this->x = x;
    this->y = y;
    this->z = z;

    this->vx = 0.0f;
    this->vy = 0.0f;
    this->vz = 0.0f;
    this->density = density;
    this->mass = 4.0f / 3.0f * 3.14159f * radius * radius * radius * density;

}

void Sphere::draw(GLint slices, GLint stacks) {

    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    glPushMatrix(); // Save the current matrix
    glTranslatef(x, y, z); // Move the sphere to the specified location
    gluSphere(quadric, radius, slices, stacks); // Draw the sphere
    glPopMatrix(); // Restore the original matrix

    gluDeleteQuadric(quadric);
}

void Sphere::draw_inner(GLint slices, GLint stacks) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    // Enable back-face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);  // Cull the front faces

    glPushMatrix(); // Save the current matrix
    glTranslatef(x, y, z); // Move the sphere to the specified location
    gluSphere(quadric, radius, slices, stacks); // Draw the sphere
    glPopMatrix(); // Restore the original matrix

    // Disable back-face culling
    glDisable(GL_CULL_FACE);

    gluDeleteQuadric(quadric);
}
    