#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>
#include <stdlib.h>
#include <time.h>
#include <print>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GLUquadric* quad;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;
float trophyX = 4.3, trophyY = 0.5, trophyZ = 4.3;
float trophy2X = 4.3, trophy2Y = 0.5, trophy2Z = -3.3;
float trophy3X = -4.3, trophy3Y = 0.5, trophy3Z = 0;
float rotationAngle = 0.0f;
unsigned int ID;
unsigned int ID2[40];
GLfloat alpha = 0.0, theta = 0.0, orbiterAlpha = -45.0, orbiterTheta = 0.0, pirateBoatTheta = 0.0;
const int screenWidth = 1200, screenHeight = 1200;
float scaleX = 1, scaleY = 1, scaleZ = 1;
float scaleeX = 1.5, scaleeY = 1.5, scaleeZ = 1.5;
static int slices = 16;
static int stacks = 16;
GLboolean scaleFlag = false, scale2Flag = false;
const float minX = -4.7f;
const float maxX = 4.7f;
const float minZ = -4.3f;
const float maxZ = 4.6f;
struct Player
{
    float x;
    float y;
    float z;
    float rotation;
};
Player player = { 0, 0.6 , 0 , 0.0f };
struct Goal {
    float x;
    float y;
    float z;
    float angle;
};
Goal goal = { 0,0,0,0 };
GLfloat yf = 0, xf = 0;
int gameTime = 60;
GLboolean  gameRunning = true, isWin = false, goalCollected = false, Trophy1collided = false, Trophy2collided = false, Trophy3collided = false;
double eyeX = -10, eyeY = 5.0, eyeZ = 10, refX = 0, refY = 0, refZ = 0;
GLboolean fanSwitch = false, door1 = false, orbiterFlag = false, pirateBoatFlag = false, pirateBoatCheck = false;
static GLubyte BoxquadIndices[6][4] =
{
    {0,2,3,1},
    {0,2,6,4},
    {2,3,7,6},
    {1,3,7,5},
    {1,5,4,0},
    {6,7,5,4}
};
static GLfloat v_box[8][3] =
{
    {0.0, 0.0, 0.0},
    {3.0, 0.0, 0.0},
    {0.0, 0.0, 3.0},
    {3.0, 0.0, 3.0},
    {0.0, 3.0, 0.0},
    {3.0, 3.0, 0.0},
    {0.0, 3.0, 3.0},
    {3.0, 3.0, 3.0},

};
static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 3.0},
    {3.0, 0.0, 3.0},
    {3.0, 0.0, 0.0},
    {0.0, 3.0, 0.0},
    {0.0, 3.0, 3.0},
    {3.0, 3.0, 3.0},
    {3.0, 3.0, 0.0}
};

static GLfloat v_trapezoid[8][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 3.0},
    {3.0, 0.0, 3.0},
    {3.0, 0.0, 0.0},
    {0.5, 3.0, 0.5},
    {0.5, 3.0, 2.5},
    {2.5, 3.0, 2.5},
    {2.5, 3.0, 0.5}
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {5, 1, 2, 6},
    {3, 7, 4, 0},
    {2, 3, 7, 6},
    {0, 4, 5, 1}
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {5, 1, 2, 6},
    {3, 7, 4, 0},
    {2, 3, 7, 6},
    {0, 4, 5,1}
};

GLfloat colors[13][3] = {
   {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
    {1, 1, 0}, {1, 0, 1}, {0, 1, 1},
    {1, 0.5, 0.5}, {0.5, 1, 0.5}, {0.5, 0.5, 1},
   {0.5, 0.5, 0.5} };

void materialProperty()
{
    glColor3f(1, 1, 1);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void drawTrophy() {
    glPushMatrix();
    glColor3f(0.8, 0.7, 0.1);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    materialProperty();
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    GLUquadricObj* quadric;
    quadric = gluNewQuadric();
    glColor3f(0.8, 0.7, 0.1);
    gluDisk(quadric, 0.0f, 1.0f, 32, 32);
    glColor3f(0.8, 0.7, 0.1);
    gluCylinder(quadric, 1.0f, 1.0f, 0.5f, 32, 32);
    glTranslatef(0.0f, 0.0f, 0.5f);
    glColor3f(0.8, 0.7, 0.1);
    gluDisk(quadric, 0.0f, 1.0f, 32, 32);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.0f);
    quadric = gluNewQuadric();
    glColor3f(0.8, 0.7, 0.1);
    gluCylinder(quadric, 0.5f, 0.8f, 1.5f, 32, 32);
    glTranslatef(0.0f, 0.0f, 1.5f);
    glColor3f(0.8, 0.7, 0.1);
    gluDisk(quadric, 0.0f, 0.8f, 32, 32);
    gluDeleteQuadric(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0f, 0.75f, 0.0f); 
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.8, 0.7, 0.1);
    glutSolidTorus(0.1f, 0.3f, 16, 32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.0f, 0.75f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.8, 0.7, 0.1);
    glutSolidTorus(0.1f, 0.3f, 16, 32);
    glPopMatrix();
    glPopMatrix();
}

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
            v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
            v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine = 90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTorus(innerRadius, outerRadius, nsides, rings);
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(1.0, 16, 16);
}

void rings()
{
    for (float i = -3.5; i >= -17.5; i -= 1)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(0.2, 0.2, 0.2);
        drawTorus(1, 0, 0, 0.5, 0, 0, 1.5, 7.5, 32, 64);
        glPopMatrix();
    }

    for (float i = -3; i >= -17; i -= 1)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(0.2, 0.2, 0.2);
        drawTorus(1, 1, 1, 0.5, 0.5, 0.5, 1.5, 7.5, 32, 64);
        glPopMatrix();
    }

}

void drawFerrisWheel() {
    const int numCabin = 12;
    float wheelRadius = 3.0f;
    float cabinSize = 0.2f;
    float rotationAngle = 360.0f / numCabin;
    //wheel as two circles
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, wheelRadius + cabinSize, 0.0f);
    glutWireTorus(cabinSize / 4, wheelRadius, 50, 50);
    glutWireTorus(cabinSize / 4, wheelRadius + cabinSize, 50, 50);
    glPopMatrix();
    //cabins
    for (int i = 0; i < numCabin; i++) {
        glPushMatrix();
        glRotatef(i * rotationAngle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, wheelRadius, 0.0f);
        glColor3f(0.9f, 0.9f, 0.9f);
        glutSolidCube(cabinSize);
        glPopMatrix();
    }
    // stand 
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(-wheelRadius / 2, 0.0f, 0.0f);
    glScalef(cabinSize / 2, wheelRadius * 2, cabinSize / 2);
    glutSolidCube(1.0);
    glPopMatrix();
    // Right leg
    glPushMatrix();
    glTranslatef(wheelRadius / 2, 0.0f, 0.0f);
    glScalef(cabinSize / 2, wheelRadius * 2, cabinSize / 2);
    glutSolidCube(1.0);
    glPopMatrix();
    // Base of the Ferris wheel
    glPushMatrix();
    glTranslatef(0.0f, -cabinSize, 0.0f);
    glScalef(wheelRadius, cabinSize / 2, cabinSize / 2);
    glutSolidCube(1.0);
    glPopMatrix();
    // Cross beams for support
    glPushMatrix();
    glTranslatef(0.0f, wheelRadius, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(cabinSize / 4, wheelRadius * 1.5, cabinSize / 4);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, wheelRadius, 0.0f);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(cabinSize / 4, wheelRadius * 1.5, cabinSize / 4);
    glutSolidCube(1.0);
    glPopMatrix();
    glFlush();
}

void drawBox()
{
    materialProperty();
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_box[BoxquadIndices[i][0]][0], v_box[BoxquadIndices[i][0]][1], v_box[BoxquadIndices[i][0]][2],
            v_box[BoxquadIndices[i][1]][0], v_box[BoxquadIndices[i][1]][1], v_box[BoxquadIndices[i][1]][2],
            v_box[BoxquadIndices[i][2]][0], v_box[BoxquadIndices[i][2]][1], v_box[BoxquadIndices[i][2]][2]);

        glVertex3fv(&v_box[BoxquadIndices[i][0]][0]); glTexCoord2f(1, 1);
        glVertex3fv(&v_box[BoxquadIndices[i][1]][0]); glTexCoord2f(1, 0);
        glVertex3fv(&v_box[BoxquadIndices[i][2]][0]); glTexCoord2f(0, 0);
        glVertex3fv(&v_box[BoxquadIndices[i][3]][0]); glTexCoord2f(0, 1);
    }
    glEnd();
}

void drawFencePost(GLfloat* color) {
    GLUquadricObj* quadric = gluNewQuadric();
    glColor3fv(color);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.05, 0.05, 0.8, 12, 2);
    glPopMatrix();
}

void drawFencePlank(GLfloat* color) {
    glColor3fv(color);
    glPushMatrix();
    glScalef(0.7, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawFenceSegment(GLfloat* color) {
    //left post
    glPushMatrix();
    glTranslatef(-0.35, 0.25, 0);
    drawFencePost(color);
    glPopMatrix();
    //right post
    glPushMatrix();
    glTranslatef(0.35, 0.25, 0);
    glPopMatrix();
    //three planks
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0, 0.2 * (i + 1), 0);
        drawFencePlank(color);
        glPopMatrix();
    }
}

void drawFence() {
    int numberOfSegments = 13;
    for (int i = 0; i < numberOfSegments; i++) {
        glPushMatrix();
        glTranslatef(i * 0.75, 0, 0);

        int timeSegment = (int)(gameTime / 2) % numberOfSegments; // change color kol 2 secs
        GLfloat color[3];
        color[0] = colors[(i + timeSegment) % numberOfSegments][0];
        color[1] = colors[(i + timeSegment) % numberOfSegments][1];
        color[2] = colors[(i + timeSegment) % numberOfSegments][2];
        glColor3fv(color);

        drawFenceSegment(color);
        glPopMatrix();
    }
}

void drawBench() {
    float benchLength = 2.0f;
    float benchWidth = 0.5f;
    float benchHeight = 0.2f;
    float legHeight = 0.5f;
    float legWidth = 0.1f;
    float legDepth = 0.1f;
    glColor3f(0.8, 0.4, 0.0);
    glPushMatrix();
    glTranslatef(0.0f, legHeight + benchHeight / 2, 0.0f);
    glScalef(benchLength, benchHeight, benchWidth);
    glutSolidCube(1.0);
    glPopMatrix();
    float legPosX = benchLength / 2 - legWidth / 2;
    float legPosZ = benchWidth / 2 - legDepth / 2;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * legPosX, legHeight / 2, j * legPosZ);
            glScalef(legWidth, legHeight, legDepth);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

void drawGround() {
    glPushMatrix();
    glColor3f(1, 1, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(-5, 0, -5);
    glVertex3f(5, 0, -5);
    glVertex3f(5, 0, 5);
    glVertex3f(-5, 0, 5);
    glEnd();
    glPopMatrix();
}

void setupLights() {
    GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
    GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
    GLfloat shininess[] = { 50 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
    GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 640 / 480, 0.001, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);
}

void drawCylinder2(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.5, 1.5, 19, 32, 32);

}

void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, baseRadius, topRadius, height, slices, stacks);
    gluDeleteQuadric(quad);
}

void drawCone(float base, float height, int slices, int stacks) {
    glutSolidCone(base, height, slices, stacks);
}

void drawTree(float trunkRadius, float trunkHeight, float bottomFoliageRadius, float topFoliageRadius, int foliageLayers) {
    // Draw the trunk
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glTranslatef(0.0f, trunkHeight / 2, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawCylinder(trunkRadius, trunkRadius, trunkHeight, 16, 4);
    glPopMatrix();
    // Draw the foliage layers
    float layerHeight = trunkHeight;
    float layerStep = (bottomFoliageRadius - topFoliageRadius) / foliageLayers;
    float currentRadius = bottomFoliageRadius;
    for (int i = 0; i < foliageLayers; ++i) {
        glColor3f(0.0f, 0.5f + (0.5f / foliageLayers) * i, 0.0f);
        glPushMatrix();
        glTranslatef(0.0f, layerHeight, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(currentRadius, trunkHeight * 0.6, 16, 4);
        glPopMatrix();

        layerHeight += trunkHeight * 0.1;
        currentRadius -= layerStep;
    }
}

void ferrisWheelSeat()
{
    //seat
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glScalef(0.5, 0.2, 1.5);
    drawCube1(0.804, 0.361, 0.361, 0.403, 0.1805, 0.1805);
    glPopMatrix();
    //seat belt rod
    glPushMatrix();
    glTranslatef(1.3, 0.7, 0);
    glScalef(0.02, 0.02, 1.5);
    drawCube1(0, 0, 0, 0, 0, 0.0);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[4]);
    //back
    glPushMatrix();
    glScalef(0.2, 0.5, 1.5);
    drawBox();
    glPopMatrix();
    //seat right side
    glPushMatrix();
    glScalef(0.5, 0.5, 0.02);
    drawBox();
    glPopMatrix();
    //seat left side
    glPushMatrix();
    glTranslatef(0, 0, 4.445);
    glScalef(0.5, 0.5, 0.02);
    drawBox();
    glPopMatrix();
    //bottom bent part
    glPushMatrix();
    glTranslatef(1.48, -0.5, 0);
    glRotatef(-45, 0, 0, 1);
    glScalef(0.15, 0.02, 1.5);
    drawBox();
    glPopMatrix();
    //bottom straight part
    glPushMatrix();
    glTranslatef(1.8, -0.8, 0);
    //glRotatef(-20, 0, 0, 1);
    glScalef(0.16, 0.02, 1.5);
    drawBox();
    glPopMatrix();
    //bottom farthest part
    glPushMatrix();
    glTranslatef(2.25, -0.8, 0);
    glScalef(0.02, 0.1, 1.5);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void wheel()
{
    glPushMatrix();
    glScalef(1, 1, 2);
    drawSphere(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();
    glPushMatrix();
    drawTorus(1, 1, 0.3, 0.5, 0.5, 0.15, 0.5, 10.0, 32, 64);
    glPopMatrix();
    //the big lines
    for (int i = 0; i < 180; i += 30)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glScalef(6.6, 0.1, 0.5);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.867, 0.627, 0.867, 0.4335, 0.3135, 0.4335, 100);
        glPopMatrix();
    }
}

void bulbsOnFerrisWheel()
{
    for (int i = 0; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        drawSphere(1, 1, 1, 0.5, 0.5, 0.5);
        glPopMatrix();
    }

    for (int i = 15; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        drawSphere(1, 0, 0, 0.5, 0, 0);
        glPopMatrix();
    }

    for (int i = 30; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        drawSphere(0, 0, 1, 0, 0, 0.5);
        glPopMatrix();
    }
}

void drawPlayer() {
    glPushMatrix();
    glTranslated(0, 0, 5);
    // cloth
    glPushMatrix();
    glTranslated(0, -1.6, -6);
    glRotated(-90, 0.1, 0, 0);
    glColor3ub(255, 95, 0);
    glScaled(1.5, 1.7, 2);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();
    //3black
    glPushMatrix();
    glTranslated(0, -.5, -4.7);
    glRotated(90, 1, 0, 0);
    glScaled(.1, .1, .1);
    glColor3f(0, 0, 0);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, -.8, -4.6);
    glRotated(90, 1, 0, 0);
    glScaled(.1, .1, .1);
    glColor3f(0, 0, 0);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, -1.1, -4.5);
    glRotated(90, 1, 0, 0);
    glScaled(.1, .1, .1);
    glColor3f(0, 0, 0);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    //second
    glPushMatrix();
    glTranslated(0, -.35, -5.7);
    glRotated(-90, 0.1, 0, 0);
   glColor3ub(0, 234, 0);
    glScaled(1, 1, 1);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();

    //face
    glPushMatrix();
    glTranslated(0, .8, -5.8);
    glRotated(90, 1, 0, 0);
    glScaled(1.5, 1.5, 1.5);
    glColor3ub(244, 224, 190);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    //left leg
    glPushMatrix();
    glTranslated(-.74, -2.2, -6);
    glRotated(90, 1, 0, 0);
    glScaled(.9, .9, .9);
    glColor3ub(128, 128, 128);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-.74, -2.8, -6.1);
    glRotated(-90, 0.1, 0, 0);
    glColor3ub(0, 0, 0);
    glScaled(.95, 1, 1);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();

    //right leg
    glPushMatrix();
    glTranslated(.74, -2.2, -6);
    glRotated(90, 1, 0, 0);
    glScaled(.9, .9, .9);
    glColor3ub(128, 128, 128);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.74, -2.8, -6.1);
    glRotated(-90, 0.1, 0, 0);
    glColor3ub(0, 0, 0);
    glScaled(.95, 1, 1);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();

    //hand
    glPushMatrix();
    glTranslated(1, -.55, -6);
    glRotated(60, 0, 1, 0);
    glScaled(1.3, .2, .5);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1, -.55, -6);
    glRotated(-60, 0, 1, 0);
    glScaled(1.3, .2, .5);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    //mouse
    glPushMatrix();
    glTranslated(0, .3, -4.5);
    glRotated(180, 0, .5, -1);
    glScaled(.2, -.2, .2);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();

    //white
    glPushMatrix();
    glTranslated(0, 0.1, -3);
    glRotated(-180, 0, .5, -1);
    glColor3f(1, 1, 1);
    glScaled(.1, .1, .1);
    glutSolidCube(.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-.04, 0.1, -3);
    glRotated(-180, 0, .5, -1);
    glColor3f(1, 1, 1);
    glScaled(.1, .1, .1);
    glutSolidCube(.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(.04, 0.1, -3);
    glRotated(-180, 0, .5, -1);
    glColor3f(1, 1, 1);
    glScaled(.1, .1, .1);
    glutSolidCube(.3);
    glPopMatrix();

    //eye
    //right
    glPushMatrix();
    glTranslated(.32, .73, -4);
    glRotated(90, 1, 0, 0);
    glScaled(.1, .1, .1);
    glColor3f(0, 0, 0);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();
    //white
    glPushMatrix();
    glTranslated(.35, .8, -4.3);
    glRotated(90, 0, 1, 0);
    glScaled(.2, .3, .2);
    glColor3f(1, 1, 1);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();


    //left
    glPushMatrix();
    glTranslated(-.32, .73, -4);
    glRotated(90, 1, 0, 0);
    glScaled(.1, .1, .1);
    glColor3f(0, 0, 0);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    //white
    glPushMatrix();
    glTranslated(-.35, .8, -4.3);
    glRotated(90, 0, 1, 0);
    glScaled(.2, .3, .2);
    glColor3f(1, 1, 1);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();
    //upeye
    //left
    glPushMatrix();
    glTranslated(-.4, 1.3, -4.3);
    glRotated(120, 1, 0, 1);
    glScaled(.05, .2, .2);
    glColor3f(0, 0, 0);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();

    //right
    glPushMatrix();
    glTranslated(.35, 1.3, -4.3);
    glRotated(120, 1, 0, 1);
    glScaled(.05, .2, .2);
    glColor3f(0, 0, 0);
    glutSolidCone(1, 2, slices, stacks);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}


void ferrisWheel()
{
    glPushMatrix();
    glTranslatef(-.2, 0, -1);
    glRotatef(-75, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    drawCube1(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.6, 0, -1);
    glRotatef(-105, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    drawCube1(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-.2, 0, 6);
    glRotatef(-75, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    drawCube1(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.6, 0, 6);
    glRotatef(-105, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    drawCube1(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -19.5, 2.5);
    glScalef(4, 0.5, 3);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
    glPopMatrix();
    for (float j = -9; j <= 19; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, 11);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, 11);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(4, -17, 11);
    glScalef(10, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4, -18, 11);
    glScalef(10, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4, -19, 11);
    glScalef(10, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -20, 11);
    glRotatef(-alpha, 0, 1, 0);
    for (float j = 0; j <= 4; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, 0, 0);
        glScalef(0.1, 1.5, 0.1);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(j, 4.4, 0.2);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    for (float j = 1; j <= 3; j += 1)
    {
        glPushMatrix();
        glTranslatef(0, j, 0);
        glScalef(1.5, 0.05, 0.1);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();
    }
    glPopMatrix();
    for (float j = -3; j <= 9; j += 2)
    {
        glPushMatrix();
        glTranslatef(-15, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-15, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(-15, -17, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -18, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -19, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    for (float j = -3; j <= 9; j += 2)
    {
        glPushMatrix();
        glTranslatef(19, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(19, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(19, -17, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(19, -18, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(19, -19, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-theta, 0, 0, 1);
    glScalef(1.5, 1.5, 1);
    wheel();
    glPushMatrix();
    glTranslatef(0, 0, 5);
    wheel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, 5.5);
    bulbsOnFerrisWheel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, -0.5);
    bulbsOnFerrisWheel();
    glPopMatrix();
    glPushMatrix();
    glScalef(0.1, 0.05, 1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    for (int j = 0; j <= 360; j += 30)
    {
        glPushMatrix();
        glRotatef(j, 0, 0, 1);
        for (int i = 1; i <= 7; i++)
        {
            glPushMatrix();
            glTranslatef(i, 0, 0);
            glScalef(0.1, 0.05, 1.5);
            drawCube1(0.780, 0.082, 0.522, 0.39, 0.041, 0.261);
            glPopMatrix();
        }
        glPopMatrix();
    }
    for (int i = 0; i < 360; i += 30)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0.9);
        glRotatef(-i, 0, 0, 1);
        glRotatef(theta, 0, 0, 1);
        glScalef(1, 1, 0.8);
        ferrisWheelSeat();
        glPopMatrix();
    }
    glPopMatrix();
}


void drawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(v_trapezoid[TquadIndices[i][0]][0], v_trapezoid[TquadIndices[i][0]][1], v_trapezoid[TquadIndices[i][0]][2],
            v_trapezoid[TquadIndices[i][1]][0], v_trapezoid[TquadIndices[i][1]][1], v_trapezoid[TquadIndices[i][1]][2],
            v_trapezoid[TquadIndices[i][2]][0], v_trapezoid[TquadIndices[i][2]][1], v_trapezoid[TquadIndices[i][2]][2]);

        glVertex3fv(&v_trapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}

void orbiter()
{
    //1st torus at the bottom
    rings();
    glPushMatrix();
    glTranslatef(0, -18, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(1, 1, 1, 0.5, 0.5, 0.5, 2, 8, 32, 64);
    glPopMatrix();

    //2nd torus at the bottom
    glPushMatrix();
    glTranslatef(0, -18.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(1, 0, 0, 0.5, 0, 0, 2, 10, 32, 64);
    glPopMatrix();

    //the sphere
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2.5, 2.5, 2.5);
    drawSphere(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    //fence in the front
    for (float j = -10; j <= 16; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, 17);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, 17);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    //horizontal lines of the front fence
    glPushMatrix();
    glTranslatef(2.5, -17, 17);
    glScalef(9, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -18, 17);
    glScalef(9, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -19, 17);
    glScalef(9, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //gate
    glPushMatrix();
    glTranslatef(-15.5, -20, 17);
    glRotatef(-alpha, 0, 1, 0);
    for (float j = 0; j <= 4; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, 0, 0);
        glScalef(0.1, 1.5, 0.1);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, 4.4, 0.2);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    for (float j = 1; j <= 3; j += 1)
    {
        glPushMatrix();
        glTranslatef(0, j, 0);
        glScalef(1.5, 0.05, 0.1);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();
    }
    glPopMatrix();


    //fence in the back
    for (float j = -14; j <= 16; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, -17);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, -17);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    ///horizontal lines of the back fence
    glPushMatrix();
    glTranslatef(0, -17, -17);
    glScalef(10.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -18, -17);
    glScalef(10.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -19, -17);
    glScalef(10.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //fence in the right
    for (float j = -17; j <= 15; j += 2)
    {
        glPushMatrix();
        glTranslatef(16, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(16, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    //the horizontal lines
    glPushMatrix();
    glTranslatef(16, -17, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -18, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -19, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //fence in the left
    for (float j = -17; j <= 17; j += 2)
    {
        glPushMatrix();
        glTranslatef(-16, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-16, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    //
    glPushMatrix();
    glTranslatef(-16, -17, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16, -18, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16, -19, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //translating the rotating part down
    glPushMatrix();
    glTranslatef(0, -5, 0);

    //rotating part
    glPushMatrix();
    glRotatef(orbiterTheta, 0, 1, 0);
    //seat
    for (int i = 0; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glRotatef(orbiterAlpha, 0, 0, 1);
        glRotatef(0, 0, 1, 0);
        glTranslatef(15, 0, -2);
        glRotatef(-0, 0, 1, 0);
        glRotatef(-orbiterAlpha, 0, 0, 1);
        ferrisWheelSeat();
        glPopMatrix();

        glPushMatrix();
        glRotatef(orbiterAlpha, 0, 0, 1);
        glScalef(5.1, 0.2, 0.2);
        drawCube1(0, 0, 1, 0, 0, 0.5);
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();

    glPopMatrix();

}

void boatBody()
{
    glPushMatrix();
    glColor3d(0.2, 1, 0.6);

    glPushMatrix();
    glTranslatef(-1.3, 0, 0);
    glScalef(3.7, 0.1, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 1.5, 1.5);
    glScalef(5.5, 1, 0.1);
    glRotatef(180, 0, 0, 1);
    glTranslatef(-1.25, -1.5, -1.25);
    glColor3d(0.2, 1, 0.6);
    drawTrapezoid(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5, -1.5);
    glScalef(5.5, 1, 0.1);
    glRotatef(180, 0, 0, 1);
    glTranslatef(-1.25, -1.5, -1.25);
    glColor3d(0.2, 1, 0.6);
    drawTrapezoid(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.5, 1.5, 0);
    glRotatef(-42, 0, 0, 1);
    glScalef(0.1, 1.3, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.1, 1.5, 0);
    glRotatef(42, 0, 0, 1);
    glScalef(0.1, 1.3, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    for (float i = -6; i <= 2; i += 2)
    {
        glPushMatrix();
        glTranslatef(i, 0, -1.5);
        glScalef(0.1, 1, 1);
        glColor3d(0.2, 1, 0.6);
        drawCube1(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
        glPopMatrix();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[3]);
    glPushMatrix();
    glTranslatef(-6.9, 0, 1.7);
    glScalef(3.7, 1, 0.01);
    glColor3d(0.2, 1, 0.6);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.9, 0, -1.7);
    glScalef(3.7, 1, 0.01);
    glColor3d(0.2, 1, 0.6);
    drawBox();
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pirateBoat()
{
    glPushMatrix();
    glColor3d(0.2, 1, 0.6);
    glPushMatrix();
    glTranslatef(0.5, -19.5, 0);
    glScalef(6, 0.5, 4);
    glTranslatef(-1.5, -1.5, -1.5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -5.5, 0);
    glPushMatrix();
    glTranslatef(0, 0, -4);
    glScalef(0.2, 0.2, 0.5);
    glColor3d(0.2, 1, 0.6);
    drawCylinder2(1, 0, 0, 0.5, 0, 0.5);
    glPopMatrix();
    //boat body
    glPushMatrix();
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glTranslatef(1.5, -12, 0);
    glColor3d(0.2, 1, 0.6);
    boatBody();
    glPopMatrix();
    //stand on the front
    glPushMatrix();
    glTranslatef(0, 0, 1.4);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glColor3d(0.2, 1, 0.6);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-55, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    //right stand
    glPushMatrix();
    glRotatef(-125, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPopMatrix();
    //stand on the back
    glPushMatrix();
    glTranslatef(0, 0, -1.6);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glColor3d(0.2, 1, 0.6);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-55, 0, 0, 1);
    glColor3d(0.2, 1, 0.6);
    glScalef(4, 0.28, 0.1);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    //right stand
    glPushMatrix();
    glRotatef(-125, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPopMatrix();
    //base stand at the front
    glPushMatrix();
    glTranslatef(0, 0, 5);
    glColor3d(0.2, 1, 0.6);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-60, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    //right stand
    glPushMatrix();
    glRotatef(-120, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.055);
    glPopMatrix();
    glPopMatrix();
    //base stand at the back
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glColor3d(0.2, 1, 0.6);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-60, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    //right stand
    glPushMatrix();
    glRotatef(-120, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    glColor3d(0.2, 1, 0.6);
    drawCube1(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void drawStreetLamp() {
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    glColor3f(0.5f, 0.5f, 0.5f); 
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 
    gluCylinder(quadratic, 0.1f, 0.1f, 2.0f, 32, 32); 
    glPopMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); 
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.5f, 0.0f, 0.5f, 32, 32); 
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); 
    glPushMatrix();
    glTranslatef(0.0f, 1.95f, 0.0f);
    gluSphere(quadratic, 0.1f, 32, 32);
    glPopMatrix();
    gluDeleteQuadric(quadratic);
}

void displayText(float x, float y, float z, const char* string) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    GLdouble model[16], proj[16];
    GLint view[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);
    GLdouble textPosX, textPosY, textPosZ;
    gluProject(x, y, z, model, proj, view, &textPosX, &textPosY, &textPosZ);
    textPosY = h - textPosY;
    glRasterPos2f(textPosX, textPosY);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': // move eye upwards along Y axis
        eyeY += 1.0;
        break;
    case 's': // move eye downwards along Y axis
        eyeY -= 1.0;
        break;
    case 'a': // move eye left along X axis
        eyeX -= 1.0;
        break;
    case 'd': // move eye right along X axis
        eyeX += 1.0;
        break;
    case 'o':  //zoom out
        eyeZ += 1;
        break;
    case 'i': //zoom in
        eyeZ -= 1;
        break;
    case 'q': //back to default eye point and ref point
        eyeX = 0.0; eyeY = 2.0; eyeZ = 10.0;
        refX = 0.0; refY = 0.0; refZ = 0.0;
        upX = 0; upY = 1.0; upZ = 0;
        break;
    case 'j': // move ref upwards along Y axis
        refY += 1.0;
        break;
    case 'n': // move ref downwards along Y axis
        refY -= 1.0;
        break;
    case 'b': // move ref left along X axis
        refX -= 1.0;
        break;
    case 'm': // move eye right along X axis
        refX += 1.0;
        break;
    case 'k':  //move ref away from screen/ along z axis
        refZ += 1;
        break;
    case 'l': //move ref towards screen/ along z axis
        refZ -= 1;
        break;


    case '1': //orbiter
        if (orbiterFlag == false) {
            orbiterFlag = true; break;
        }
        else if (orbiterFlag == true) {
            orbiterFlag = false; break;
        }
    case '2': //ferriswheel
        if (fanSwitch == false) {
            fanSwitch = true; break;
        }
        else {
            fanSwitch = false; break;
        }
    case '3': //scale el benches
        if (scaleFlag == false) {
            scaleX = scaleY = scaleZ = 0.75;
            scaleFlag = true; break;

        }
        else if (scaleFlag == true) {
            scaleX = scaleY = scaleZ = 1.0;
            scaleFlag = false; break;
        }
    case '4': //trees
        if (scale2Flag == false) {
            scaleeX = scaleeY = scaleeZ = 1.0;
            scale2Flag = true; break;
        }
        else if (scale2Flag == true) {
            scaleeX = scaleeY = scaleeZ = 1.5;
            scale2Flag = false; break;
        }
    case '5': //pirate boat
        if (pirateBoatFlag == false) {
            pirateBoatFlag = true; break;
        }
        else if (pirateBoatFlag == true) {
            pirateBoatFlag = false; break;
        }
    case '6': // Top view
        eyeX = 0.0f; eyeY = 10.0f; eyeZ = 0.0f;  
        refX = 0.0f; refY = 0.0f; refZ = 0.0f; 
        upX = 0.0f; upY = 0.0f; upZ = -1.0f;
        break;
    case '7': // Front view
        eyeX = 0.0f; eyeY = 3.0f; eyeZ = 10.0f;  
        refX = 0.0f; refY = 0.0f; refZ = 0.0f; 
        upX = 0.0f; upY = 1.0f; upZ = 0.0f;
        break;
    case '8': // Side view
        eyeX = 10.0f; eyeY = 3.0f; eyeZ = 0.0f;
        refX = 0.0f; refY = 0.0f; refZ = 0.0f;  
        upX = 0.0f; upY = 1.0f; upZ = 0.0f;
        break;
    case 27:    // Escape key
        exit(1);
    }

    glutPostRedisplay();
}

void movePlayerForward() {
    float radian = player.rotation * (M_PI / 180.0f);
    float moveStep = 0.1;
    float newX = player.x + sin(radian) * moveStep;
    float newZ = player.z + cos(radian) * moveStep;
    if (newX < maxX && newX > minX && newZ < maxZ && newZ > minZ) {
        player.x = newX;
        player.z = newZ;
    }
}

void movePlayerBack() {
    //  float radian = player.rotation * (M_PI / 180.0f); // Convert degrees to radians
    //  float moveStep = 0.1; // This is your movement speed

      // Calculate the new position
    //  float newX = player.x - sin(radian) * moveStep; // Update X based on rotation
    //  float newZ = player.z - cos(radian) * moveStep; // Update Z based on rotation

      // Boundary checks
     // if (newX < maxX && newX > minX) {
     //     player.x = newX;
    //  }
     // if (newZ < maxZ && newZ > minZ) {
    //      player.z = newZ;
    //  }
    player.rotation += 180.0f;
    if (player.rotation < 0.0f) player.rotation += 360.0f;
    if (player.rotation >= 360.0f) player.rotation -= 360.0f;

}

void movePlayerLeft() {
    player.rotation += 90.0f;
    if (player.rotation >= 360.0f) player.rotation -= 360.0f;
}

void movePlayerRight() {
    player.rotation -= 90.0f;
    if (player.rotation < 0.0f) player.rotation += 360.0f;

}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        movePlayerForward();
        break;
    case GLUT_KEY_DOWN:
        movePlayerBack();
        movePlayerForward();
        break;
    case GLUT_KEY_LEFT:
        movePlayerLeft();
        movePlayerForward();
        break;
    case GLUT_KEY_RIGHT:
        movePlayerRight();
        movePlayerForward();
        break;
    }
    glutPostRedisplay();
}

void animate()
{
    if (pirateBoatFlag == true)
    {
        if (pirateBoatCheck == true)
        {
            pirateBoatTheta += 2;
            if (pirateBoatTheta == 60)
            {
                pirateBoatCheck = false;
            }
        }
        else
        {
            pirateBoatTheta -= 2;
            if (pirateBoatTheta == -70)
            {
                pirateBoatCheck = true;
            }
        }
    }
    else
    {
        if (pirateBoatTheta < 0)
        {
            pirateBoatTheta += 1;
            if (pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
        else if (pirateBoatTheta > 0)
        {
            pirateBoatTheta -= 1;
            if (pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
    }

    if (fanSwitch == true)
    {
        theta += 2;
        if (theta > 360.0)
            theta -= 360.0 * floor(theta / 360.0);
    }

    if (orbiterFlag == true)
    {
        orbiterTheta += 3;
        if (orbiterTheta > 360.0)
            orbiterTheta -= 360.0 * floor(theta / 360.0);

        orbiterAlpha += 2;
        if (orbiterAlpha >= 45)
            orbiterAlpha = 45;
    }
    else
    {
        orbiterAlpha -= 1;
        if (orbiterAlpha <= -45)
            orbiterAlpha = -45;

        orbiterTheta += 3;
        if (orbiterAlpha == -45)
            orbiterTheta = 0;
    }



    glutPostRedisplay();

}

void fullScreen(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60, ratio, 1, 500);
    glMatrixMode(GL_MODELVIEW);
}

void drawText(const char* str, int x, int y, void* font)
{
    glRasterPos2i(x, y);
    while (*str)
    {
        glutBitmapCharacter(font, *str++);
    }
}

int getTextWidth(const char* str, void* font)
{
    int width = 0;
    while (*str)
    {
        width += glutBitmapWidth(font, *str++);
    }
    return width;
}

void drawEndScreen(bool isWin) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    const char* displayText = isWin ? "You Win!!" : "Game Over!";
    void* font = GLUT_BITMAP_HELVETICA_18;
    int textWidth = getTextWidth(displayText, font);
    drawText(displayText, (screenWidth - textWidth) / 2, screenHeight / 2, font);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

void endGame(bool isWin)
{
    gameRunning = false;
    drawEndScreen(isWin);
}

void checkCollision() {
    if (abs(player.x - trophyX) < 0.5 && abs(player.z - trophyZ) < 0.5) {
        Trophy1collided = true;
        trophyX = 100000000;
        trophyY = 100000000;
        trophyZ = 100000000;
        printf("trophy 1");
    }
    if (abs(player.x - trophy3X) < 0.5 && abs(player.z - trophy3Z) < 0.5) {
        Trophy3collided = true;
        trophy3X = 100000000;
        trophy3Y = 100000000;
        trophy3Z = 100000000;
        printf("trophy 3");
    }
    if (abs(player.x - trophy2X) < 0.5 && abs(player.z - trophy2Z) < 0.5) {
        Trophy2collided = true;
        trophy2X = 100000000;
        trophy2Y = 100000000;
        trophy2Z = 100000000;
        printf("trophy 2");
    }
}

void timer(int value)
{
    if (!gameRunning)
    {
        endGame(false);
        return;
    }
    if (gameTime > 0)
    {
        gameTime--;
        printf("Time is: %d\n", gameTime);
        printf("X %f ", player.x);
        printf("Z %f ", player.z);
        rotationAngle += 20.0f; // Increment the rotation angle
        if (rotationAngle > 360.0f) {
            rotationAngle -= 360.0f;
        }


    }
    else
    {
        if (Trophy1collided && Trophy2collided && Trophy3collided) {
            isWin = true;
        }
        gameRunning = false;
        endGame(isWin);
        return;
    }
    checkCollision();
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0); 
}


void Display() {
    if (gameRunning) {

        setupLights();
        setupCamera();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.53f, 0.81f, 0.98f, 1.0f);  // RGBA

        // Draw the ground
        drawGround();


        glPushMatrix();
        glColor3f(0.8, 0.7, 0.1);
        glTranslatef(trophyX, trophyY, trophyZ);
        // glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.3, 0.3, 0.3);
        drawTrophy();
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.8, 0.7, 0.1);
        glTranslatef(trophy2X, trophy2Y, trophy2Z);
        //   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.3, 0.3, 0.3);
        drawTrophy();
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.8, 0.7, 0.1);
        glTranslatef(trophy3X, trophy3Y, trophy3Z);
        //  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(0.3, 0.3, 0.3);
        drawTrophy();
        glPopMatrix();
        // Draw the fence on three sides
        // Back side
        glPushMatrix();
        glTranslatef(-4.5f, 0.0f, -5.0f); // Move to the back edge of the ground
        drawFence();
        glPopMatrix();

        // Left side
        glPushMatrix();
        // Move to the left edge of the ground
        glTranslatef(-5.0f, 0.0f, 4.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate the fence to align with the side
        drawFence();
        glPopMatrix();

        // Right side
        glPushMatrix();
        glTranslatef(5.0f, 0.0f, -4.0f); // Move to the right edge of the ground
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotate the fence to align with the side
        drawFence();
        glPopMatrix();
        //Draw several trees
        //glPushMatrix();
        //glTranslatef(4.0f, 0.0f, 3.0f);
        //drawTree(0.1f, 1.0f, 0.4f, 0.1f, 5); // Trunk radius, trunk height, bottom foliage radius, top foliage radius, number of foliage layers
        //glPopMatrix();
        //el 2 3al shemal
    //    glPushMatrix();
    //    glTranslatef(-4.6f, -0.5f, 0.5f);
    //    drawTree(0.1f, 1.0f, 0.4f, 0.1f, 5);
     //   glPopMatrix();
     //   glPushMatrix();
      //  glTranslatef(-4.0f, 0.0f, 4.0f);
      //  drawTree(0.1f, 1.0f, 0.4f, 0.1f, 5);
       // glPopMatrix();
        //el talata ely wara
        glPushMatrix();
        glTranslatef(-3.7f, -0.5f, -3.8f);
        glScalef(scaleeX, scaleeY, scaleeZ);
        drawTree(0.1f, 1.0f, 0.4f, 0.1f, 5);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, -0.5f, -3.8f);
        glScalef(scaleeX, scaleeY, scaleeZ);
        drawTree(0.1f, 1.0f, 0.4f, 0.1f, 5);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(3.5f, -0.5f, -3.8f);
        glScalef(scaleeX, scaleeY, scaleeZ);
        drawTree(0.1f, 1.0f, 0.4f, 0.1f, 5);
        glPopMatrix();

        //draw several benches 
        //2 ely wara
        glPushMatrix();
        glTranslatef(-2.0f, 0.0f, -4.3f);
        glScalef(scaleX, scaleY, scaleZ);
        drawBench();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(2.0f, 0.0f, -4.3f);
        glScalef(scaleX, scaleY, scaleZ);
        drawBench();
        glPopMatrix();

        //2 3al shemal
   //     glPushMatrix();
    //    glTranslatef(-4.6f, 0.0f, -2.0f);
      //  glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotate cylinder to stand upright
       // drawBench();
        //glPopMatrix();
      //  glPushMatrix();
      //  glTranslatef(-4.0f, 0.0f, 2.0f);
     //   glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotate cylinder to stand upright
      //  drawBench();
    //    glPopMatrix();

        ///el ferrisWheel hena
        glPushMatrix();
        glTranslatef(3.7f, 3.5f, 0.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.15, 0.15, 0.2);
        ferrisWheel();
        glPopMatrix();
        //EL ORBITER
        glPushMatrix();
        //   glColor3f(1.0, 0.3, 0.8);
        glTranslatef(-3.0f, 2.8f, 2.9f);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.12, 0.12, 0.12);
        orbiter();
        glPopMatrix();

        //shwayt street lamps
        glPushMatrix();
        glTranslatef(-4.5f, 0.0f, -3.8f);
        glScalef(0.6, 0.6, 0.6);
        drawStreetLamp();
        glPopMatrix();
        //Playerrr
        glPushMatrix();
        glTranslatef(player.x, player.y, player.z);
        glRotatef(player.rotation, 0.0f, 1.0f, 0.0f);
        glScalef(0.2, 0.2, 0.2);
        drawPlayer();
        glPopMatrix();

        glPushMatrix();
        glColor3d(0.2, 1, 0.6);
        glTranslatef(-3, 4.1, -1.5);
        glScalef(0.2, 0.2, 0.2);
        pirateBoat();
        glPopMatrix();


    }
    else {
        endGame(isWin);
    }glFlush();
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(1200, 1200);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("AmuseMe!");
    glutDisplayFunc(Display);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glutReshapeFunc(fullScreen);
    glutTimerFunc(0, timer, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(specialKeys);
    glShadeModel(GL_SMOOTH);
    glutIdleFunc(animate);
    glutMainLoop();
}