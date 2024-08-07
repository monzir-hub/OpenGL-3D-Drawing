/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cmath>

// Variables to track door and window angles
GLfloat doorAngle = 0.0f;
GLfloat windowAngle = 0.0f;

// Variables to track bicycle position and wheel rotation
GLfloat bicycleX = -0.8f;
GLfloat rightWheelAngle = 0.0f;
GLfloat leftWheelAngle = 0.0f;

// Function to draw a cylinder (used for wheels)
void drawCylinder(GLfloat x, GLfloat y, GLfloat radius, GLfloat height) {
    int numSegments = 100;
    GLfloat angle;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        angle = i * 2.0f * M_PI / numSegments;
        GLfloat dx = cos(angle) * radius;
        GLfloat dy = sin(angle) * radius;
        glVertex3f(x + dx, y + dy, 0.0f);
        glVertex3f(x + dx, y + dy, height);
    }
    glEnd();
    // Draw end caps
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for (int i = 0; i <= numSegments; ++i) {
        angle = i * 2.0f * M_PI / numSegments;
        glVertex3f(x + cos(angle) * radius, y + sin(angle) * radius, 0.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, height);
    for (int i = 0; i <= numSegments; ++i) {
        angle = i * 2.0f * M_PI / numSegments;
        glVertex3f(x + cos(angle) * radius, y + sin(angle) * radius, height);
    }
    glEnd();
}

void draw3DBicycle() {
    glPushMatrix();
    glTranslatef(bicycleX, -0.5f, 0.0f);

    // Draw wheels
    glPushMatrix();
    glRotatef(leftWheelAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCylinder(-0.2f, 0.0f, 0.1f, 0.02f); // Left wheel
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4f, 0.0f, 0.0f); // Position the right wheel
    glRotatef(rightWheelAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCylinder(-0.2f, 0.0f, 0.1f, 0.02f); // Right wheel
    glPopMatrix();

    // Draw frame
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(-0.2f, 0.0f, 0.01f);
        glVertex3f(0.2f, 0.1f, 0.01f);
        glVertex3f(0.2f, 0.1f, 0.01f);
        glVertex3f(0.4f, 0.0f, 0.01f);
        glVertex3f(0.2f, 0.1f, 0.01f);
        glVertex3f(0.2f, 0.3f, 0.01f);
        glVertex3f(0.15f, 0.15f, 0.01f);
        glVertex3f(0.2f, 0.3f, 0.01f);
        glVertex3f(0.25f, 0.15f, 0.01f);
        glVertex3f(0.2f, 0.3f, 0.01f);
    glEnd();

    // Draw handlebars
    glBegin(GL_LINES);
        glVertex3f(0.25f, 0.15f, 0.01f);
        glVertex3f(0.4f, 0.3f, 0.01f);
    glEnd();

    // Draw seat
    glBegin(GL_LINES);
        glVertex3f(0.15f, 0.15f, 0.01f);
        glVertex3f(0.1f, 0.3f, 0.01f);
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw the building base
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
        // Front face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        // Back face
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        // Top face
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        // Bottom face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        // Left face
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        // Right face
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    // Draw the roof
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_TRIANGLES);
        // Front
        glVertex3f(-0.55f, 0.5f, 0.5f);
        glVertex3f(0.55f, 0.5f, 0.5f);
        glVertex3f(0.0f, 0.8f, 0.5f);
        // Back
        glVertex3f(-0.55f, 0.5f, -0.5f);
        glVertex3f(0.55f, 0.5f, -0.5f);
        glVertex3f(0.0f, 0.8f, -0.5f);
        // Sides
        glVertex3f(-0.55f, 0.5f, 0.5f);
        glVertex3f(-0.55f, 0.5f, -0.5f);
        glVertex3f(0.0f, 0.8f, 0.5f);

        glVertex3f(0.55f, 0.5f, 0.5f);
        glVertex3f(0.55f, 0.5f, -0.5f);
        glVertex3f(0.0f, 0.8f, -0.5f);
    glEnd();

    // Draw the door
    glPushMatrix();
    glTranslatef(0.0f, -0.35f, 0.51f); // Move door to the bottom center
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f); // Rotate door
    glColor3f(0.3f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-0.1f, 0.0f, 0.0f);
        glVertex3f(0.1f, 0.0f, 0.0f);
        glVertex3f(0.1f, 0.3f, 0.0f);
        glVertex3f(-0.1f, 0.3f, 0.0f);
    glEnd();
    glPopMatrix();

    // Draw windows on the first floor
    glPushMatrix();
    glTranslatef(-0.35f, -0.3f, 0.51f); // Move window to the bottom left
    glRotatef(windowAngle, 0.0f, 1.0f, 0.0f); // Rotate window
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.2f, 0.0f);
        glVertex3f(0.0f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, -0.3f, 0.51f); // Move window to the bottom right
    glRotatef(windowAngle, 0.0f, 1.0f, 0.0f); // Rotate window
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.2f, 0.0f);
        glVertex3f(0.0f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    // Draw windows on the second floor
    glPushMatrix();
    glTranslatef(-0.35f, 0.1f, 0.51f); // Move window to the top left
    glRotatef(windowAngle, 0.0f, 1.0f, 0.0f); // Rotate window
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.2f, 0.0f);
        glVertex3f(0.0f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, 0.1f, 0.51f); // Move window to the top right
    glRotatef(windowAngle, 0.0f, 1.0f, 0.0f); // Rotate window
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.0f, 0.0f);
        glVertex3f(0.2f, 0.2f, 0.0f);
        glVertex3f(0.0f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    // Draw the 3D bicycle
    draw3DBicycle();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.66, 0.76, 0.71, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'o': // Open door
            doorAngle = 45.0f;
            glutPostRedisplay();
            break;
        case 'c': // Close door
            doorAngle = 0.0f;
            glutPostRedisplay();
            break;
        case 'O': // Open windows
            windowAngle = 45.0f;
            glutPostRedisplay();
            break;
        case 'C': // Close windows
            windowAngle = 0.0f;
            glutPostRedisplay();
            break;
        case 'f': // Move bicycle forward
            bicycleX += 0.1f;
            glutPostRedisplay();
            break;
        case 'b': // Move bicycle backward
            bicycleX -= 0.1f;
            glutPostRedisplay();
            break;
        case 'r': // Rotate right wheel
            rightWheelAngle += 15.0f;
            if (rightWheelAngle > 360.0f) rightWheelAngle -= 360.0f;
            glutPostRedisplay();
            break;
        case 'l': // Rotate left wheel
            leftWheelAngle += 15.0f;
            if (leftWheelAngle > 360.0f) leftWheelAngle -= 360.0f;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Building and Bicycle");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
