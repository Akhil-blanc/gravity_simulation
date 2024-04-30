#include <GL/glut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <cmath>
#include <vector>
#include "sphere.h"
#include "mouseHandler.h"
#include "keyboardHandler.h"
#include "LightSource.h"
#include "texture.h"

using namespace std;

// GLfloat Rotation = 0.0f;
// Sphere Universe(400.0f, 0.0f, 0.0f, 0.0f, 0.0f);
// Sphere Sun(3.0f, 0.0f, 0.0f, 0.0f, 2.4f);
// // Sphere Mercury("./assets/2k_earth_daymap.jpg", 0.3f, 4.0f, 0.0f, 0.0f, 5.4f);
// Sphere Venus(0.9f, 7.0f, 0.0f, 0.0f, 8.2f);
// Sphere Earth(1.0f, 10.0f, 0.0f, 0.0f, 5.1f);
// float G = 6.674e-5; // Gravitational constant
// float angle;
// float a = 6.0f;
// float b = 4.0f;
// float beta = 2.0f * M_PI / 180.0f;

void init();
void update(int value);
void display();
void drawEllipse(float a, float b, float beta);
void drawAxis(float size);

Camera appCamera(glm::vec3(0.0f, 15.0f, 145.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
glm::vec2 lastMousePos(0.0f);
vector<Sphere*> planets;

//Sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLfloat mass)
// Sphere Universe = Sphere(300, 0.0f, 0.0f, 0.0f, 0.0f);
Sphere Sun = Sphere(30, 0.0f, 0.0f, 0.0f, 500);
Sphere Mercury = Sphere(5, 10.0f, 0.0f, 0.0f, 0.4875);
Sphere Earth = Sphere(10, 28.0f, 0.0f, 0.0f, 0.5825);
Sphere Mars = Sphere(20, 50.0f, 0.0f, 0.0f, 0.5033);
Sphere Jupiter = Sphere(40, 70.0f, 0.0f, 0.0f, 0.5033);

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // init();
    
    // Define light properties
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 1.0f, 0.78f, 0.78f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 0.78f, 0.78f, 1.0f }; // Warm yellow color
    GLfloat light_specular[] = { 1.0f, 0.78f, 0.78f, 1.0f }; // Warm yellow color

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    // Set light attenuation
    GLfloat constantAttenuation = 0.005f;
    GLfloat linearAttenuation = 0.001f;
    GLfloat quadraticAttenuation = 0.0005f;
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantAttenuation);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);


    // Define material properties for the Sun
    GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Ambient reflection
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.0f, 1.0f }; // Diffuse reflection (yellow color)
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Specular reflection (white)
    GLfloat mat_shininess[] = { 100.0f }; // Shininess (controls the size of the specular highlight)

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
    gluPerspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glm::mat4 viewMatrix = appCamera.GetViewMatrix();
    glMultMatrixf(glm::value_ptr(viewMatrix));


    // glTranslatef(0.0f, 0.0f, -cameraDistance);
    // glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    // glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    // gluLookAt(0.0, 15.0, 125,  // eye position
    //               0.0, 0.0, 0.0,  // look at position
    //               0.0, 1.0, 0.0); // up direction

    // gluLookAt(-5.0, 180.0, 0.0,  // eye position
    //               0.0, 0.0, 0.0,  // look at position
    //               0.0, 0.0, -1.0); // up direction
    // // Draw the plane
    // glColor3f(0.5f, 0.5f, 0.5f); // Gray color
    // glBegin(GL_QUADS);
    // glVertex3f(-500.0f, -1.0f, -500.0f);
    // glVertex3f(-500.0f, -1.0f, 500.0f);
    // glVertex3f(500.0f, -1.0f, 500.0f);
    // glVertex3f(500.0f, -1.0f, -500.0f);
    // glEnd();
    
    for (Sphere* planet: planets)
    {
        if (planet!= &Sun) 
        {
            planet->draw(30, 30);  
            planet->draw_trace();
            planet->draw_space_time_distortion(10);  

            glColor3f(1.0f, 1.0f, 1.0f);  
        }  
        // planet->draw_space_time_distortion(30);
    }

    // Universe.draw(30, 30);
    // GLuint UniverseTexture;
    // loadTexture("../assets/space.jpg", UniverseTexture);
    // draw_texturedobject_inner(UniverseTexture, Universe, 10, 10);

    
    glDisable(GL_LIGHTING);
    Sun.draw(30, 30);
    // GLuint SunTexture;
    // loadTexture("../assets/2k_sun.jpg", SunTexture);
    // draw_texturedobject(SunTexture, Sun, 30, 30);
    glEnable(GL_LIGHTING);
    // GLuint MercuryTexture;
    // loadTexture("../assets/2k_mercury.jpg", MercuryTexture);
    // draw_texturedobject(MercuryTexture, Mercury, 30, 30);
    // Mercury.draw(30, 30);

    // GLuint MarsTexture;
    // loadTexture("../assets/2k_mars.jpg", MarsTexture);
    // draw_texturedobject(MarsTexture, Mars, 30, 30);
    // Mars.draw(30, 30);
    // GLuint EarthTexture;
    // loadTexture("../assets/2k_earth_daymap.jpg", EarthTexture);
    // draw_texturedobject(EarthTexture, Earth, 30, 30);
    // Earth.draw(30, 30);

    glFlush();
    glutSwapBuffers();
}

void update(int value)
{
    for (Sphere* planet : planets)
    {
        planet->update_position(planets);        
    }
    
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
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
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Gravity Simulation");
    planets.push_back(&Sun);
    planets.push_back(&Mercury);
    planets.push_back(&Earth);
    planets.push_back(&Mars);
    // planets.push_back(&Jupiter);
    // Sphere::set_kinematics(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat ax, GLfloat ay, GLfloat az)
    Sun.set_kinematics(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Mercury.set_kinematics(0.0f, 0.0f, 3.031f, 0.0f, 0.0f, 0.0f);
    Earth.set_kinematics(0.0f, 0.0f, 4.031f, 0.0f, 0.0f, 0.0f);
    Mars.set_kinematics(0.0f, 0.0f, 3.031f, 0.0f, 0.0f, 0.0f);
    Jupiter.set_kinematics(0.0f, 0.0f, 2.031f, 0.0f, 0.0f, 0.0f);

     // Initialize OpenGL
     init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000/60, update, 0); // Start the update loop
    glutMainLoop();
    return 0;
}
