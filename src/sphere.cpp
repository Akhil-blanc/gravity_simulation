// sphere.cpp
#include "sphere.h"

Sphere::Sphere(const char* filename) {
    textureID = SOIL_load_OGL_texture(
        filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        std::cerr << "Error loading texture image: " << SOIL_last_result() << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Sphere::draw(GLfloat radius, GLint slices, GLint stacks, GLfloat x, GLfloat y, GLfloat z) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    glPushMatrix(); // Save the current matrix
    glTranslatef(x, y, z); // Move the sphere to the specified location
    gluSphere(quadric, radius, slices, stacks); // Draw the sphere
    glPopMatrix(); // Restore the original matrix

    gluDeleteQuadric(quadric);
}