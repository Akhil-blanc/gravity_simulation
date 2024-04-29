#include "mouseHandler.h"
#include <GL/glut.h>
int lastX = 0;
int lastY = 0;
bool mouseDown = false;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 1.0f;

void handleMouse(int button, int state, int x, int y) {
    if (button == 3 || button == 4) { // Scroll up or down
        if (button == 3)
            cameraDistance -= 0.1f;
        else if (button == 4)
            cameraDistance += 0.1f;

        

        glutPostRedisplay(); // Trigger redraw
    }else if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = true;
            lastX = x;
            lastY = y;
        } else if (state == GLUT_UP) {
            mouseDown = false;
        }
    }
}

void handleMouseMove(int x, int y) {
    if (mouseDown) {
        int deltaX = x - lastX;
        int deltaY = y - lastY;
        lastX = x;
        lastY = y;

        cameraAngleX += (float)deltaX * 0.1f;
        cameraAngleY += (float)deltaY * 0.1f;

        // Limit camera angle Y to avoid flipping the view
        if (cameraAngleY > 89.0f) {
            cameraAngleY = 89.0f;
        } else if (cameraAngleY < -89.0f) {
            cameraAngleY = -89.0f;
        }

        glutPostRedisplay(); // Trigger redraw
    }
}