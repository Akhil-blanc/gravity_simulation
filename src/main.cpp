#include <GL/glut.h>
#include <iostream>
#include <SOIL/SOIL.h> // Include SOIL for image loading
#include "sphere.h"
#include "mouseHandler.h"
using namespace std;


Sphere earth("assets/2k_earth_daymap.jpg");
Sphere mercury("assets/2k_earth_daymap.jpg");

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(0.0f, 0.0f, -cameraDistance);
    glRotatef(cameraAngleX, 0.0f, 1.0f, 0.0f);
    glRotatef(cameraAngleY, 1.0f, 0.0f, 0.0f);
    
    gluLookAt(0.0, 0.0, 1.75,  // eye position
                  0.0, 0.0, -1.0,  // look at position
                  0.0, 1.0, 0.0); // up direction

    glEnable(GL_TEXTURE_2D);
    earth.draw(0.3f, 30, 30, 0.0f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, earth.textureID);
    glDisable(GL_TEXTURE_2D);

    mercury.draw(0.1f, 30, 30, 0.5f, 0.5f, 0.0f);
    
    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Textured Sphere");

    init(); // Initialize OpenGL
    glutDisplayFunc(display);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);

    glutMainLoop();
    return 0;
}
