// sphere.cpp
#include "sphere.h"

float simulation_speed = 0.8f;
float TRACES_LENGTH = 40;
Sphere::Sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLfloat mass) {

    this->radius = radius;
    this->x = x;
    this->y = y;
    this->z = z;

    this->vx = 0.0f;
    this->vy = 0.0f;
    this->vz = 0.0f;

    this->ax = 0.0f;
    this->ay = 0.0f;
    this->az = 0.0f;
    this->mass = mass;

}

void Sphere::draw(GLint slices, GLint stacks) {

    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    glPushMatrix(); // Save the current matrix
    glTranslatef(x, y, z); // Move the sphere to the specified location
    gluSphere(quadric, radius, slices, stacks); // Draw the sphere
    glPopMatrix(); // Restore the original matrix

    gluDeleteQuadric(quadric);
}

void Sphere::draw_inner(GLint slices, GLint stacks) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    // Enable back-face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);  // Cull the front faces

    glPushMatrix(); // Save the current matrix
    glTranslatef(x, y, z); // Move the sphere to the specified location
    gluSphere(quadric, radius, slices, stacks); // Draw the sphere
    glPopMatrix(); // Restore the original matrix

    // Disable back-face culling
    glDisable(GL_CULL_FACE);

    gluDeleteQuadric(quadric);
}

void Sphere::update_position(vector<Sphere*>& spheres) {

    vx += ax*simulation_speed;
    vy += ay*simulation_speed;
    vz += az*simulation_speed;

    x += vx*simulation_speed;
    y += vy*simulation_speed;
    z += vz*simulation_speed;

    ax = 0.0f;
    ay = 0.0f;
    az = 0.0f;

    bool myIndexSmaller = false;


    for (Sphere* object : spheres) {
        if (object == this) { myIndexSmaller = true; continue; }

        GLfloat distX = x - object->x;
        GLfloat distY = y - object->y;
        GLfloat distZ = z - object->z;
        GLfloat calcDist = sqrt(pow(distX, 2) + pow(distY, 2) + pow(distZ, 2));
        GLfloat inverseDist = 1 / calcDist;
        GLfloat dirX = distX * inverseDist;
        GLfloat dirY = distY * inverseDist;
        GLfloat dirZ = distZ * inverseDist;

        // apply gravity
        ax -= dirX * object->mass * pow(inverseDist, 2);
        ay -= dirY * object->mass * pow(inverseDist, 2);
        az-= dirZ * object->mass * pow(inverseDist, 2);

        // collision handling
        GLfloat offset;
        // if ((offset = calcDist - (radius + object->radius)) <= 0)
        // {
        //     x -= vx;
        //     y -= vy;
        //     z -= vz;
        // }

        if ((offset = calcDist - (radius + object->radius)) <= 0)
        {
            // Calculate the overlap between the objects
            float overlap = 0.5f * (calcDist - radius - object->radius);

            // Adjust positions
            x -= overlap * (x - object->x) / calcDist;
            y -= overlap * (y - object->y) / calcDist;
            z -= overlap * (z - object->z) / calcDist;
            object->x += overlap * (x - object->x) / calcDist;
            object->y += overlap * (y - object->y) / calcDist;
            object->z += overlap * (z - object->z) / calcDist;
        }
    }
}

void Sphere::set_kinematics(GLfloat vx, GLfloat vy, GLfloat vz, GLfloat ax, GLfloat ay, GLfloat az) {
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
    this->ax = ax;
    this->ay = ay;
    this->az = az;
}
    
void Sphere::draw_trace() {
    // vector<GLfloat> tracePoints;
    tracePoints.push_back(x);
    tracePoints.push_back(y);
    tracePoints.push_back(z);

    if (tracePoints.size() / 3 >= TRACES_LENGTH) {
        tracePoints.erase(tracePoints.begin(), tracePoints.begin() + 3);
    }

    glBegin(GL_QUADS);
    for (int i = 0; i < tracePoints.size(); i += 3) {
        GLfloat x = tracePoints[i];
        GLfloat y = tracePoints[i + 1];
        GLfloat z = tracePoints[i + 2];

        GLfloat size = 0.2f; // Size of the cube

        // Front face
        glVertex3f(x - size, y - size, z + size);
        glVertex3f(x + size, y - size, z + size);
        glVertex3f(x + size, y + size, z + size);
        glVertex3f(x - size, y + size, z + size);

        // Back face
        glVertex3f(x - size, y - size, z - size);
        glVertex3f(x + size, y - size, z - size);
        glVertex3f(x + size, y + size, z - size);
        glVertex3f(x - size, y + size, z - size);

        // Left face
        glVertex3f(x - size, y - size, z - size);
        glVertex3f(x - size, y - size, z + size);
        glVertex3f(x - size, y + size, z + size);
        glVertex3f(x - size, y + size, z - size);

        // Right face
        glVertex3f(x + size, y - size, z - size);
        glVertex3f(x + size, y - size, z + size);
        glVertex3f(x + size, y + size, z + size);
        glVertex3f(x + size, y + size, z - size);

        // Top face
        glVertex3f(x - size, y + size, z - size);
        glVertex3f(x - size, y + size, z + size);
        glVertex3f(x + size, y + size, z + size);
        glVertex3f(x + size, y + size, z - size);

        // Bottom face
        glVertex3f(x - size, y - size, z - size);
        glVertex3f(x - size, y - size, z + size);
        glVertex3f(x + size, y - size, z + size);
        glVertex3f(x + size, y - size, z - size);
    }
    glEnd();

    // tracePoints.clear();
}