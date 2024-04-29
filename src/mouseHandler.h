#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

extern int lastX;
extern int lastY;
extern bool mouseDown;
extern float cameraAngleX;
extern float cameraAngleY;
extern float cameraDistance;
void handleMouse(int button, int state, int x, int y);
void handleMouseMove(int x, int y);

#endif // MOUSE_HANDLER_H