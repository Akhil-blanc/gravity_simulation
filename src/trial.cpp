#include <GL/glut.h>
#include <cmath>

// Function to draw the ellipse
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

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -30.0f); // Move the ellipse away from the viewer
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f); // Rotate the ellipse for better visibility

    drawEllipse(5.0f, 10.0f, 20.0f * M_PI / 180.0f);

    glFlush();
}



// Initialization function
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f); // Set perspective projection
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ellipse in OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
