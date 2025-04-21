// Graphics Pgm 5 for Bailee Segars
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-2025.h"

// Author: Bailee Segars
// CS 445-01 SP25
// Architecture:
    // GLUT event-driven generation of a fish tank scene.
    // The canvas is named Fish Tank Simulation and is produced
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

static unsigned int letters;

void letters_list(float translate_x, float translate_y)
{
    letters = glGenLists(1);

    glNewList(letters, GL_COMPILE);
        glColor3f(0.0, 0.46, 0.78); // set the pen color to UAH blue
        // Letter U
        glPushMatrix();
            glTranslatef(translate_x, translate_y+150.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x, translate_y+100.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+50.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+100.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+150.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+150.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+150.0, translate_y+100.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+150.0, translate_y+150.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();

        // Letter A
        glPushMatrix();
            glTranslatef(translate_x+250.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+275.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+325.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+375.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+425.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+300.0, translate_y+100.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+325.0, translate_y+150.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+375.0, translate_y+150.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+400.0, translate_y+100.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+450.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutWireCube(1.0);
        glPopMatrix();

        // Letter H
        glPushMatrix();
            glTranslatef(translate_x+550.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+550.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+550.0, translate_y+100.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+550.0, translate_y+150.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+600.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+650.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+700.0, translate_y, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+700.0, translate_y+50.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+700.0, translate_y+100.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(translate_x+700.0, translate_y+150.0, -375.0);
            glScalef(50.0, 50.0, 1.0);
            glutSolidCube(1.0);
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
// void big_fish_animation(int id)
// {
//     if (swimming)
//     {
//         glutPostRedisplay();
//         glutTimerFunc(50, big_fish_animation, 1);
//     }
// }

// Display event handler
// Redraws the screen every time glutPostRedisplay() is called
// Sets the colors for the background and each object, then calls
// the functions to draw the objects in the scene
void display_func()
{
    // set the background color to black
    glClearColor(0.0, 0.0, 0.0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(letters);
    glFlush();
    glutSwapBuffers();  // swaps the buffers to show the fish's updated position
}


#define canvas_Width 800
#define canvas_Height 800
char canvas_Name[] = "Spinning UAH Emblem";

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glutDisplayFunc(display_func);

    letters_list(-350.0, -200.0);

    glutMainLoop();
    return 0;
}
