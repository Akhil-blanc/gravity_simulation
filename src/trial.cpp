// #include <GL/glut.h>
// #include <cmath>

// // Function to draw the ellipse
// void drawEllipse(float a, float b, float beta) {
//     glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

//     glBegin(GL_LINE_LOOP);
//     for (int theta = 0; theta <= 360; theta++) {
//         float radians = theta * M_PI / 180.0f;
//         float x = a * cos(radians) * cos(beta);
//         float y = a * cos(radians) * sin(beta);
//         float z = b * sin(radians);
//         glVertex3f(x, y, z);
//     }
//     glEnd();
// }

// // Display function
// void display() {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glLoadIdentity();

//     glTranslatef(0.0f, 0.0f, -30.0f); // Move the ellipse away from the viewer
//     glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // Rotate the ellipse for better visibility

//     drawEllipse(5.0f, 10.0f, 20.0f * M_PI / 180.0f);

//     glFlush();
// }



// // Initialization function
// void init() {
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(45.0f, 1.0f, 1.0f, 100.0f); // Set perspective projection
//     glMatrixMode(GL_MODELVIEW);
// }

// // Main function
// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("Ellipse in OpenGL");
//     init();
//     glutDisplayFunc(display);
//     glutMainLoop();
//     return 0;
// }

#include <GL/glut.h>
#include <vector>
#include <cmath>
using namespace std;

class Object
{
public:
    Object(float positionX, float positionY, float initialVelocityX, float initialVelocityY, float mass, unsigned radius, float colorR, float colorG, float colorB);
    
    void Update(vector<Object*>& objects);
    void Render();
    
    float getMass() { return mass; }
    float getRadius() { return radius; }
    float getPositionX() { return positionX; }
    float getPositionY() { return positionY; }
    float getVelocityX() { return velocityX; }
    float getVelocityY() { return velocityY; }

    // Utils
    float calcDistance(float aX, float aY, float bX, float bY);
    
private:
    // Rendering characteristics
    unsigned radius;
    float colorR, colorG, colorB;
    
    // Physics related
    float positionX, positionY;
    float velocityX, velocityY;
    float accelerationX, accelerationY;
    float mass;
};

std::vector<Object*> objects;

void display();
void reshape(int w, int h);
void update(int value);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(960, 720);
    glutCreateWindow("Title");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / 60, update, 0);

    // Initialize objects
        // Add some objects
    // objects.push_back(new Object(590, 300, 0, 2.4f, 0.0025f, 10, 0, 1, 0));
    objects.push_back(new Object(350, 300, 0, -3.5f, 0.0025f, 10, 0, 1, 1));
    objects.push_back(new Object(190, 300, 0, 2.031f, 0.5f, 10, 1, 1, 0));
    objects.push_back(new Object(480, 300, 0, 1.8f, 3.0f, 10, 0, 0, 1));
    objects.push_back(new Object(300, 300, 0, 0, 500, 20, 1, 1, 1));

    glutMainLoop();
    return 0;
}

Object::Object(float positionX, float positionY, float initialVelocityX, float initialVelocityY, float mass, unsigned radius, float colorR, float colorG, float colorB)
{
    this->positionX = positionX;
    this->positionY = positionY;
    this->velocityX = initialVelocityX;
    this->velocityY = initialVelocityY;
    this->mass = mass;
    this->radius = radius;
    this->colorR = colorR;
    this->colorG = colorG;
    this->colorB = colorB;
}

void Object::Update(vector<Object*>& objects)
{
    velocityX += accelerationX;
    velocityY += accelerationY;
    positionX += velocityX;
    positionY += velocityY;
    
    // Reset acceleration
    accelerationX = 0;
    accelerationY = 0;

    bool myIndexSmaller = false;

    for (Object* object : objects)
    {
        if (object == this) { myIndexSmaller = true; continue; }

        // gravity calculation
        GLfloat distX = positionX - object->positionX;
        GLfloat distY = positionY - object->positionY;
        GLfloat calcDist = sqrt(pow(distX, 2) + pow(distY, 2));
        GLfloat inverseDist = 1 / calcDist;
        GLfloat dirX = distX * inverseDist;
        GLfloat dirY = distY * inverseDist;

        // apply gravity
        accelerationX -= dirX * object->mass * pow(inverseDist, 2);
        accelerationY -= dirY * object->mass * pow(inverseDist, 2);

        // collision handling
        GLfloat offset;
        if ((offset = calcDist - (radius + object->radius)) <= 0)
        {
            positionX -= velocityX;
            positionY -= velocityY;
        }
    }

}

void Object::Render()
{
    glPushMatrix();
    glColor3f(colorR, colorG, colorB);
    glTranslatef(positionX, positionY, 0);

    const int segments = 100; // Number of segments to approximate the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0); // Center of the circle
    
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * float(i) / float(segments); // Calculate the angle for each segment
        float x = radius * cosf(angle); // Calculate x coordinate
        float y = radius * sinf(angle); // Calculate y coordinate
        glVertex2f(x, y); // Vertex of the circle
    }
    
    glEnd();

    glPopMatrix();
}




void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (Object* object : objects)
    {
        object->Render();
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value)
{
    for (Object* object : objects)
    {
        object->Update(objects);
    }
    
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
}

float Object::calcDistance(float aX, float aY, float bX, float bY)
{
    return sqrt(pow(aX - bX, 2) + pow(aY - bY, 2));
}

