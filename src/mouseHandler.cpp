// #include "mouseHandler.h"
// #include <GL/glut.h>
// int lastX = 0;
// int lastY = 0;
// bool mouseDown = false;
// float cameraAngleX = 0.0f;
// float cameraAngleY = 0.0f;
// float cameraDistance = 1.0f;

// void handleMouse(int button, int state, int x, int y) {
//     if (button == 3 || button == 4) { // Scroll up or down
//         if (button == 3)
//             cameraDistance -= 0.1f;
//         else if (button == 4)
//             cameraDistance += 0.1f;

        

//         glutPostRedisplay(); // Trigger redraw
//     }else if (button == GLUT_LEFT_BUTTON) {
//         if (state == GLUT_DOWN) {
//             mouseDown = true;
//             lastX = x;
//             lastY = y;
//         } else if (state == GLUT_UP) {
//             mouseDown = false;
//         }
//     }
// }

// void handleMouseMove(int x, int y) {
//     if (mouseDown) {
//         int deltaX = x - lastX;
//         int deltaY = y - lastY;
//         lastX = x;
//         lastY = y;

//         cameraAngleX += (float)deltaX * 0.1f;
//         cameraAngleY += (float)deltaY * 0.1f;

//         // Limit camera angle Y to avoid flipping the view
//         if (cameraAngleY > 89.0f) {
//             cameraAngleY = 89.0f;
//         } else if (cameraAngleY < -89.0f) {
//             cameraAngleY = -89.0f;
//         }

//         glutPostRedisplay(); // Trigger redraw
//     }
// }

#include "mouseHandler.h"

// int lastX = 0, lastY = 0;
// float rotationX = 0.0f, rotationY = 0.0f;
// bool mousePressed = false;
extern glm::vec2 lastMousePos;
extern Camera appCamera; // Declare appCamera from another file
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        lastMousePos.x = x;
        lastMousePos.y = y;
    }
}

void motion(int x, int y)
{
    float deltaX = x - lastMousePos.x;
    float deltaY = y - lastMousePos.y;

    const float sensitivity = 0.1f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;

    glm::vec3 viewDir = appCamera.GetViewDir();
    glm::vec3 rightVec = appCamera.GetRightVector();
    glm::vec3 upVec = appCamera.GetUpVector();

    glm::vec3 eye = appCamera.GetEye();
    glm::vec3 lookAt = appCamera.GetLookAt();

    // Calculate the amount of rotation given the mouse movement.
    float viewportWidth = glutGet(GLUT_WINDOW_WIDTH);
    float viewportHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float deltaAngleX = (2 * M_PI / viewportWidth); // a movement from left to right = 2*PI = 360 deg
    float deltaAngleY = (M_PI / viewportHeight);  // a movement from top to bottom = PI = 180 deg
    float xAngle = deltaX * deltaAngleX;
    float yAngle = deltaY * deltaAngleY;

    // Extra step to handle the problem when the camera direction is the same as the up vector
    float cosAngle = glm::dot(viewDir, upVec);
    if (cosAngle * glm::sign(deltaAngleY) > 0.99f)
        deltaAngleY = 0;

    // Rotate the camera around the pivot point on the first axis.
    glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), xAngle, upVec);
    glm::vec4 position = (rotationMatrixX * glm::vec4(eye - lookAt, 1.0f)) + glm::vec4(lookAt, 1.0f);

    // Rotate the camera around the pivot point on the second axis.
    glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), yAngle, rightVec);
    glm::vec3 finalPosition = glm::vec3((rotationMatrixY * (position - glm::vec4(lookAt, 1.0f))) + glm::vec4(lookAt, 1.0f));

    // Update the camera view (we keep the same lookat and the same up vector)
    appCamera.SetCameraView(finalPosition, lookAt, upVec);

    lastMousePos.x = x;
    lastMousePos.y = y;

    glutPostRedisplay();
}