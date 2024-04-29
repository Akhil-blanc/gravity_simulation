// LightSource.h
#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <GL/glut.h>

class LightSource {
public:
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat position[4];

    LightSource(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat position[4]) {
        for (int i = 0; i < 4; i++) {
            this->ambient[i] = ambient[i];
            this->diffuse[i] = diffuse[i];
            this->specular[i] = specular[i];
            this->position[i] = position[i];
        }
    }

    void enable() {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, this->ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, this->diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, this->specular);
        glLightfv(GL_LIGHT0, GL_POSITION, this->position);
    }
};

#endif // LIGHTSOURCE_H