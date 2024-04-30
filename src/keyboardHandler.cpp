#include "keyboardHandler.h"

extern Camera appCamera; // Declare appCamera from another file
void keyboard(unsigned char key, int x, int y)
{
    const float cameraSpeed = 1.0f;
    const float cameraRotateSpeed = glm::radians(0.5f); // reduced rotation speed
    glm::vec3 eye = appCamera.GetEye();
    glm::vec3 lookAt = appCamera.GetLookAt();
    glm::vec3 upVec = appCamera.GetUpVector();
    glm::vec3 rightVec = glm::normalize(glm::cross(upVec, appCamera.GetViewDir())); // right vector
    switch (key)
    {
    case 'w': // Zoom in
        eye += cameraSpeed * appCamera.GetViewDir();
        lookAt += cameraSpeed * appCamera.GetViewDir();
        break;
    case 's': // Zoom out
        eye -= cameraSpeed * appCamera.GetViewDir();
        lookAt -= cameraSpeed * appCamera.GetViewDir();
        break;
    case 'a': // Pan left
        eye -= glm::normalize(glm::cross(appCamera.GetViewDir(), upVec)) * cameraSpeed;
        lookAt -= glm::normalize(glm::cross(appCamera.GetViewDir(), upVec)) * cameraSpeed;
        break;
    case 'd': // Pan right
        eye += glm::normalize(glm::cross(appCamera.GetViewDir(), upVec)) * cameraSpeed;
        lookAt += glm::normalize(glm::cross(appCamera.GetViewDir(), upVec)) * cameraSpeed;
        break;
    case 'z': // Rotate left
        lookAt = eye + glm::vec3(glm::rotate(glm::mat4(1.0f), cameraRotateSpeed, upVec) * glm::vec4(lookAt - eye, 0.0f));
        break;
    case 'c': // Rotate right
        lookAt = eye + glm::vec3(glm::rotate(glm::mat4(1.0f), -cameraRotateSpeed, upVec) * glm::vec4(lookAt - eye, 0.0f));
        break;
    case 'q': // Rotate up
        lookAt = eye + glm::vec3(glm::rotate(glm::mat4(1.0f), cameraRotateSpeed, rightVec) * glm::vec4(lookAt - eye, 0.0f));
        break;
    case 'e': // Rotate down
        lookAt = eye + glm::vec3(glm::rotate(glm::mat4(1.0f), -cameraRotateSpeed, rightVec) * glm::vec4(lookAt - eye, 0.0f));
        break;
    }

    appCamera.SetCameraView(eye, lookAt, upVec);
    glutPostRedisplay();
}