#include <GL/glut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <cmath>
#include "sphere.h"
#include "mouseHandler.h"
#include "LightSource.h"
using namespace std;

GLfloat Rotation = 0.0f;
Sphere Sun("./assets/2k_earth_daymap.jpg", 3.0f, 0.0f, 0.0f, 0.0f, 2.4f);
Sphere Mercury("./assets/2k_earth_daymap.jpg", 0.3f, 4.0f, 0.0f, 0.0f, 5.4f);
Sphere Venus("./assets/2k_earth_daymap.jpg", 0.9f, 7.0f, 0.0f, 0.0f, 5.2f);
Sphere Earth("./assets/2k_earth_daymap.jpg", 1.0f, 10.0f, 0.0f, 0.0f, 5.1f);
float G = 6.674e-11; // Gravitational constant


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Define light properties
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 1.0 }; // Yellow light
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Set light attenuation
    GLfloat constantAttenuation = 0.2;
    GLfloat linearAttenuation = 0.1f;
    GLfloat quadraticAttenuation = 0.01f;
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);


    // Define material properties for the Sun
    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 }; // Yellow color
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

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
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    gluLookAt(0.0, 0.0, 25,  // eye position
                  0.0, 0.0, -1.0,  // look at position
                  0.0, 1.0, 0.0); // up direction

    glEnable(GL_TEXTURE_2D);
    Sun.draw(30, 30);
    glBindTexture(GL_TEXTURE_2D, Sun.textureID);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix(); // Save the current matrix
    glRotatef(Rotation, 0.0f, 1.0f, 0.0f); // Rotate 
    Mercury.draw(30, 30);
    glPopMatrix(); // Restore the current matrix

    glPushMatrix(); // Save the current matrix
    glRotatef(Rotation, 0.0f, 1.0f, 0.0f); // Rotate 
    Venus.draw(30, 30);
    glPopMatrix(); // Restore the current matrix
    
    glPushMatrix(); // Save the current matrix
    glRotatef(Rotation, 0.0f, 1.0f, 0.0f); // Rotate 
    Earth.draw(30, 30);
    glPopMatrix(); // Restore the current matrix

    glutSwapBuffers();
}

void update(int value) {
    Rotation += 0.5f; // Adjust this value to change the speed of rotation
    if (Rotation > 360.0f) {
        Rotation -= 360.0f;
    }

    glutPostRedisplay(); // Trigger a redraw
    glutTimerFunc(16, update, 0); // Update every 16 milliseconds (about 60 FPS)
}


void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT0); // Enable light #0
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    // Define light properties
    GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 0.78f, 0.58f, 1.0f }; // Warm yellow color
    GLfloat lightSpecular[] = { 1.0f, 0.78f, 0.58f, 1.0f }; // Warm yellow color
    GLfloat lightPosition[] = { 2.0f, 2.0f, 3.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

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
    glutTimerFunc(16, update, 0); // Start the update loop
    glutMainLoop();
    return 0;
}
