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

#include <cmath>
#include <random>

float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

float lerp(float t, float a, float b) { return a + t * (b - a); }

float grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y,
          v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float perlinNoise(float x, float y, float z) {
    static int permutation[] = { 151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,251,34,
        242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,138,236,205,93,
        222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
    };
    static int p[512];
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < 256; i++) p[256 + i] = p[i] = permutation[i];
        initialized = true;
    }

    int X = (int)floor(x) & 255,
        Y = (int)floor(y) & 255,
        Z = (int)floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    float u = fade(x),
          v = fade(y),
          w = fade(z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
        B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
                                 grad(p[BA], x - 1, y, z)),
                         lerp(u, grad(p[AB], x, y - 1, z),
                              grad(p[BB], x - 1, y - 1, z))),
                 lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
                              grad(p[BA + 1], x - 1, y, z - 1)),
                      lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                           grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

void Sphere::draw_space_time_distortion(GLint resolution) {
    GLfloat step = radius / resolution;

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix(); // Save the current matrix
    glTranslatef(x, y - radius, z); // Move the grid to the sphere's location

    // Draw the distorted grid
    for (GLfloat x = -radius; x <= radius; x += step) {
        for (GLfloat z = -radius; z <= radius; z += step) { // Change y to z here
            // Calculate the gravitational field strength at this point
            GLfloat dist = sqrt(x * x + z * z); // Change y to z here
            GLfloat field_strength = mass / (dist * dist); // Simplified, adjust as needed

            // Calculate the displacement based on the gravitational field
            GLfloat displacement = field_strength * 15.0f; // Adjust the factor as needed

            // Add some randomness to the displacement for a more 3D look
            displacement += perlinNoise(x, displacement, z) * 5.0f; // Adjust the factor as needed

            // Draw distorted grid point
            glBegin(GL_QUADS);
            glVertex3f(x, -displacement, z); // Change z to displacement here
            glVertex3f(x + step, -displacement, z); // Change z to displacement here
            glVertex3f(x + step, -displacement, z + step); // Change z to displacement here
            glVertex3f(x, -displacement, z + step); // Change z to displacement here
            glEnd();
        }
    }

    glPopMatrix(); // Restore the original matrix

    // Disable transparency
    glDisable(GL_BLEND);
}