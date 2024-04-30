
#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H
#include "camera.h" 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

void mouse(int button, int state, int x, int y);
void motion(int x, int y);

#endif // MOUSE_HANDLER_H