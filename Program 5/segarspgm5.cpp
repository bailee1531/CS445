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
    // display_func sets the lighting and material properties,
    // draws the spindle above the letters, calls the display
    // lists to draw each letter, and calls the display list
    // to draw the sphere.
    // Display events are triggered by the timer handler, which
    // is in letter_animation.
    // During the first display event, the timer handler is
    // called. The timer handler triggers a display
    // event after 25ms to redraw the scene with the
    // UAH emblem in its new position.

// variables used to create the display lists
static unsigned int lettersUH;  // display list to draw the U and the H
static unsigned int letterA;    // display list to draw the A
static unsigned int innerSphere;    // display list to draw the sphere inside of A
int theta = 0;  // rotation value

GLfloat uah_blue[] = {0.0, 0.46, 0.78};     // defines the uah blue color
GLfloat medium_gray[] = {0.5, 0.5, 0.5};    // defines the medium gray color
GLfloat dull_gray[] = {0.66, 0.66, 0.66};   // defines the dull gray color
GLfloat apple_red[] = {1.0, 0.03, 0.0};     // defines the candy apple red color
GLfloat ambient_light[] = {0.25, 0.25, 0.25, 1.0};   // defines ambient light
GLfloat diffuse_light[] = {0.5, 0.5, 0.5, 1.0};      // defines diffuse light
GLfloat specular_light[] = {0.75, 0.75, 0.75, 1.0};  // defines specular light
GLfloat position_light[] = {0.0, 0.0, 1.0, 0.0};    // defines position property
GLfloat specular_material[] = {0.7, 0.7, 0.7, 1.0}; // defines material specularity
GLfloat shininess_material[] = {30.0};  // defines shininess

// Uses three display lists to draw the letters and the sphere
// The objects are made using glut objects
// Each letter is made up of 10 cubes that are 50x50x50
// The letters U and H are made of solid cubes
// The letter A is made of wireframe cubes
// The sphere is solid and has a diameter of 50
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
// to show the emblem's updated position
// glutTimerFunc needs to be called after
// 25 ms to complete the rotation in ~2 seconds
// int id: id to be used for the timer handler
void letter_animation(int id)
{
    theta = theta % 360;    // reset to 0 once theta is 360
    theta += 4;     // rotate in 4 degree increments

    glutPostRedisplay();
    glutTimerFunc(25, letter_animation, 1);
}

// Display event handler
// Redraws the screen every time glutPostRedisplay() is called
// Sets the colors for the background and each object, draws
// the spindle, then sets the material properties and
// calls the display lists to draw the objects in the scene
void display_func()
{
    // set the background color to black
    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update only the front of the spindle, and specify ambient and diffuse light
    // color is dull gray
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, dull_gray);
    glBegin(GL_TRIANGLES);
        glVertex3f(10.0, 0.0, -400.0);
        glVertex3f(35.0, 75.0, -400.0);
        glVertex3f(-15.0, 75.0, -400.0);
    glEnd();

    glPushMatrix();
        // use the favorite toy method to rotate
        glTranslatef(10.0, 0.0, -400.0);    // move to an axis
        glRotatef(theta, 0.0, 1.0, 0.0);    // rotate about the axis
        glTranslatef(-10.0, 0.0, 400.0);    // put it back

        // update only the front of the letters, and specify ambient and diffuse light
        // color is uah blue
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, uah_blue);
        glCallList(lettersUH);

        // update only the front of the letter, and specify ambient and diffuse light
        // color is medium gray
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, medium_gray);
        glCallList(letterA);

        // update only the front of the sphere, and specify ambient and diffuse light
        // color is candy apple red
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

    // only need to enable these at the start
    glEnable(GL_LIGHT0);     // includes light0 in lighting equation
    glEnable(GL_LIGHTING);   // associates color with vertices
    glEnable(GL_DEPTH_TEST); // enables depth comparisons
    glEnable(GL_CULL_FACE);  // enables culling

    // applies previous definitions of light properties to GL parameters
    // associated with light0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);    // applies ambient light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);    // applies diffuse light
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);  // applies specular light
    glLightfv(GL_LIGHT0, GL_POSITION, position_light);  // applies light position

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_material);     // applies material specularity
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess_material);   // applies material shininess

    glShadeModel(GL_SMOOTH);    // interpolates colors
    glCullFace(GL_BACK);    // specifies that the back face is culled so only the front is rendered

    glutDisplayFunc(display_func);
    letters_list();

    // first timer event handler call
    glutTimerFunc(25, letter_animation, 0);

    glutMainLoop();
    return 0;
}
