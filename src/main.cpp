#include <GL/glut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <cmath>
#include "sphere.h"
#include "mouseHandler.h"
#include "LightSource.h"
#include "texture.h"
using namespace std;

GLfloat Rotation = 0.0f;
Sphere Universe(30.0f, 0.0f, 0.0f, 0.0f, 0.0f);
Sphere Sun(3.0f, 0.0f, 0.0f, 0.0f, 2.4f);
// Sphere Mercury("./assets/2k_earth_daymap.jpg", 0.3f, 4.0f, 0.0f, 0.0f, 5.4f);
Sphere Venus(0.9f, 7.0f, 0.0f, 0.0f, 8.2f);
Sphere Earth(1.0f, 10.0f, 0.0f, 0.0f, 5.1f);
float G = 6.674e-5; // Gravitational constant
float angle;
float a = 6.0f;
float b = 4.0f;
float beta = 2.0f * M_PI / 180.0f;

void init();
void update(int value);
void display();
void drawEllipse(float a, float b, float beta);
void drawAxis(float size);


void update_planet_position(Sphere &planet, Sphere &sun, float a, float b, float beta) {
    float distance = sqrt(pow(planet.x - sun.x, 2) + pow(planet.y - sun.y, 2) + pow(planet.z - sun.z, 2));
    float force = G * planet.mass * sun.mass / pow(distance, 2);
    float acceleration = force / planet.mass;
    float vx = acceleration * (sun.x - planet.x) / distance;
    float vy = acceleration * (sun.y - planet.y) / distance;
    float vz = acceleration * (sun.z - planet.z) / distance;
    planet.vx += vx;
    planet.vy += vy;
    planet.vz += vz;
    angle += 5.0f * (acceleration);

    if (angle > 2 * 3.14159265359) // Reset angle to keep object moving in loop
        angle -= 2 * 3.14159265359;
    planet.x = a * cos(angle) * cos(beta);
    planet.y = a * cos(angle) * sin(beta);
    planet.z = b * sin(angle);
}

void drawEllipse(float a, float b, float beta) {
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    glBegin(GL_LINE_LOOP);
    for (int theta = 0; theta <= 360; theta++) {
        float radians = theta * M_PI / 180.0f;
        float x = a * cos(radians) * cos(beta);
        float y = a * cos(radians) * sin(beta);
        float z = b * sin(radians);
        glVertex3f(x, y, z);
    }
    glEnd();
}


void drawAxis(float size) {
    glBegin(GL_LINES);

    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);

    // Y axis in green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);

    // Z axis in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glEnable(GL_DEPTH_TEST);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    init();
    
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

    gluLookAt(0.0, 2.0, 25,  // eye position
                  0.0, 0.0, 0.0,  // look at position
                  0.0, 1.0, 0.0); // up direction

    // gluLookAt(0.0, 15.0, 0.0,  // eye position
    //               0.0, 0.0, 0.0,  // look at position
    //               0.0, 0.0, -1.0); // up direction


    // Universe.draw(30, 30);
    GLuint UniverseTexture;
    loadTexture("../assets/space.jpg", UniverseTexture);
    draw_texturedobject_inner(UniverseTexture, Universe, 30, 30);


    // Sun.draw(30, 30);
    GLuint SunTexture;
    loadTexture("../assets/2k_sun.jpg", SunTexture);
    draw_texturedobject(SunTexture, Sun, 30, 30);

    glPushMatrix(); // Save the current matrix
    glRotatef(Rotation, 0.0f, 0.0f, 0.0f); // Rotate 
    // Mercury.draw(30, 30);
    glPopMatrix(); // Restore the current matrix

    glPushMatrix(); // Save the current matrix
    drawEllipse(a+3, b+1, beta+2.0f * M_PI / 180.0f);
    // glRotatef(Rotation, 0.0f, 1.0f, 0.0f); // Rotate
    update_planet_position(Venus, Sun, a+3, b+1, beta+2.0f * M_PI / 180.0f);
     
    // GLuint VenusTexture;
    // loadTexture("../assets/2k_earth_daymap.jpg", VenusTexture);
    // draw_texturedobject(VenusTexture, Venus, 30, 30);
    // glPopMatrix(); // Restore the current matrix
    
    glPushMatrix(); // Save the current matrix
    drawEllipse(a, b, beta);
    // glRotatef(Rotation, 0.0f, 1.0f, 0.0f); // Rotate 
    update_planet_position(Earth, Sun, a, b, beta);
    
    GLuint EarthTexture;

    loadTexture("../assets/2k_earth_daymap.jpg", EarthTexture);
    draw_texturedobject(EarthTexture, Earth, 30, 30);
    Earth.draw(30, 30);

    glPopMatrix(); // Restore the current matrix
    glFlush();

    // glLoadIdentity();
    

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

    //init(); // Initialize OpenGL
    glutDisplayFunc(display);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);
    glutTimerFunc(16, update, 0); // Start the update loop
    glutMainLoop();
    return 0;
}
