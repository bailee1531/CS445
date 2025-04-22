// Graphics Pgm 5 for Bailee Segars
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-2025.h"

// Author: Bailee Segars
// CS 445-01 SP25
// Architecture:
    // GLUT event-driven generation of a UAH emblem scene.
    // The canvas is named Spinning UAH Emblem and is produced
    // via the display event handler, which is in display_func.
    // display_func calls a function to draw the big fish, a
    // function to draw the little fish, and a function
    // to draw the cactus decoration on the scene.
    // The keyboard press is handled via the keyboard
    // event handler, which is in key_pressed.
    // Display events are triggered by the timer handler.
    // During the first display event, the timer handler is
    // called. The timer handler triggers a display
    // event after 50ms to redraw the scene with the fish in
    // its new position 20 times per second. The display handler
    // redraws the scene until a keyboard event is triggered.
    // When the letter 'Q' is pressed, the keyboard handler
    // sets the boolean value 'swimming' to false, which
    // is then evaluated every time the timer handler is
    // triggered. Once this value evaluates to false, the
    // timer handler no longer triggers display events.

static unsigned int lettersUH;
static unsigned int letterA;
static unsigned int innerSphere;
int theta = 0;

GLfloat uah_blue[] = {0.0, 0.46, 0.78};
GLfloat medium_gray[] = {0.5, 0.5, 0.5};
GLfloat dull_gray[] = {0.66, 0.66, 0.66};
GLfloat apple_red[] = {1.0, 0.03, 0.0};
GLfloat ambient_light[] = {0.25, 0.25, 0.25};
GLfloat diffuse_light[] = {0.5, 0.5, 0.5};
GLfloat specular_light[] = {0.75, 0.75, 0.75};
GLfloat position_light[] = {0.0, 0.0, 1.0, 0.0};
GLfloat specular_material[] = {0.7, 0.7, 0.7};
GLfloat shininess_material[] = {30.0};

void letters_list()
{
    lettersUH = glGenLists(1);
    glNewList(lettersUH, GL_COMPILE);
        // Letter U
        // bottom row
        glPushMatrix();
            glTranslatef(-340.0, -175.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-290.0, -175.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-240.0, -175.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-190.0, -175.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();

        // second row
        glPushMatrix();
            glTranslatef(-340.0, -125.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-190.0, -125.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();

        // third row
        glPushMatrix();
            glTranslatef(-340.0, -75.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-190.0, -75.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();

        // top row
        glPushMatrix();
            glTranslatef(-340.0, -25.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-190.0, -25.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();


        // Letter H
        // bottom row
        glPushMatrix();
            glTranslatef(210.0, -175.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(360.0, -175.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();

        // second row
        glPushMatrix();
            glTranslatef(210.0, -125.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(260.0, -125.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(310.0, -125.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(360.0, -125.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();

        // third row
        glPushMatrix();
            glTranslatef(360.0, -75.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(210.0, -75.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();

        // top row
        glPushMatrix();
            glTranslatef(210.0, -25.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(360.0, -25.0, -400.0);
            glutSolidCube(50.0);
        glPopMatrix();
    glEndList();

    letterA = glGenLists(1);
    glNewList(letterA, GL_COMPILE);
        // Letter A
        // bottom row
        glPushMatrix();
            glTranslatef(-90.0, -175.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(110.0, -175.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();

        // second row
        glPushMatrix();
            glTranslatef(-65.0, -125.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-15.0, -125.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(35.0, -125.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(85.0, -125.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();

        // third row
        glPushMatrix();
            glTranslatef(-40.0, -75.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(60.0, -75.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();

        // top row
        glPushMatrix();
            glTranslatef(-15.0, -25.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(35.0, -25.0, -400.0);
            glutWireCube(50.0);
        glPopMatrix();
    glEndList();

    innerSphere = glGenLists(1);
    glNewList(innerSphere, GL_COMPILE);
        // Sphere in the A
        glPushMatrix();
            glTranslatef(10.0, -75.0, -400.0);
            glutSolidSphere(25.0, 20, 20);
        glPopMatrix();
    glEndList();
}


// Timer handler
// Redraws the scene with glutPostRedisplay()
// to show the big fish's updated position
// if the boolean 'swimming' is true.
// There are 1000 ms in a second, so
// glutTimerFunc needs to be called after
// 50 ms to be called 20 times per second
// int id: id to be used for the timer handler
void letter_animation(int id)
{
    theta = theta % 360;
    theta += 4;
    glutPostRedisplay();
    glutTimerFunc(100, letter_animation, 1);
}

// Display event handler
// Redraws the screen every time glutPostRedisplay() is called
// Sets the colors for the background and each object, then calls
// the functions to draw the objects in the scene
void display_func()
{
    // set the background color to black
    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dull_gray);
    glBegin(GL_TRIANGLES);
        glVertex3f(10.0, 0.0, -400.0);
        glVertex3f(35.0, 75.0, -400.0);
        glVertex3f(-15.0, 75.0, -400.0);
    glEnd();

    glPushMatrix();
        glTranslatef(10.0, 0.0, -400.0);
        glRotatef(theta, 0.0, 1.0, 0.0);
        glTranslatef(-10.0, 0.0, 400.0);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, uah_blue);
        glCallList(lettersUH);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, medium_gray);
        glCallList(letterA);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, apple_red);
        glCallList(innerSphere);
    glPopMatrix();

    glutSwapBuffers();  // swaps the buffers to show the updated position
}


#define canvas_Width 800
#define canvas_Height 800
char canvas_Name[] = "Spinning UAH Emblem";

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position_light);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_material);
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);

    glutDisplayFunc(display_func);
    letters_list();
    glutTimerFunc(100, letter_animation, 0);

    glutMainLoop();
    return 0;
}
