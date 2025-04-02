// Graphics Pgm 4 for Bailee Segars
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-2025.h"
#include <stdio.h>

// Author: Bailee Segars
// CS 445-01 SP25
// Architecture:
    // GLUT event-driven generation of a spacecraft landing scene.
    // The canvas is named Spacecraft Landing and is produced
    // via the display event handler, which is in display_func.
    // display_func calls a function to draw the text and a
    // function to draw the spacecraft on the scene.
    // The keyboard press is handled via the keyboard
    // event handler, which is in key_pressed.
    // Display events are triggered by the keyboard handler and
    // the timer handler. When the letter 'M' or 'I' is pressed,
    // the keyboard handler sets gravity to the corresponding
    // gravity constant and starts a timer event. When the
    // letter 'H' or 'J' is pressed, the keyboard handler shifts
    // the x value of the spacecraft and triggers a display event
    // to redraw the scene. The timer handler calls
    // spacecraft_animation, which triggers a display event
    // after 50ms to redraw the scene with the spacecraft in
    // its new position 20 times per second. The display handler
    // redraws the scene until the program is closed.


// Pantone Spun Sugar: (0.722, 0.875, 0.925)
// Pantone True Red: (0.749, 0.098, 0.196)
// Pantone Tangelo: (1.0, 0.494, 0.015)
// Cactus: (0.180, 0.376, 0.129)

// Draws the larger fish
void draw_big_fish()
{
    glPushMatrix();
    glTranslatei(0, 0, -400);
    glScalef(17.67, 17.67, 17.67);
    glutWireOctahedron();
    glPopMatrix();
}

// Draws the smaller fish
void draw_little_fish()
{
    glPushMatrix();
    glTranslatei(75, 50, -400);
    glScalef(17.67, 17.67, 17.67);
    glutWireOctahedron();
    glPopMatrix();
}

void draw_cactus()
{

}

// Timer handler
// Redraws the scene with glutPostRedisplay()
// to show the spacecraft's updated placement
// There are 1000 ms in a second, so
// glutTimerFunc needs to be called after
// 50 ms to be called 20 times per second
// velTime is incremented by 0.05 so the
// spacecraft's falling rate is updated 20
// times per second
// The spacecraft's y axis is updated with the gravity formula given
// in class. This formula does not allow the displacement
// caused by the 'U' key to affect the velocity factor
// int id: id to be used for the timer handler
void spacecraft_animation(int id)
{
    velTime += 0.05;
    y_axis = (int)((0.0*velTime) + 582.33 - ((gravity/2.0)*velTime*velTime));   // gravity effect formula
    glutPostRedisplay();
    glutTimerFunc(50, spacecraft_animation, 1);
}

// Display event handler
// Redraws the screen every time glutPostRedisplay() is called
// Determines if the starting text should be displayed based on the boolean value
// Calls the function to draw the spacecraft and the function to draw the fuel
// text
// Draws the horizontal red line and the landing zone
void display_func()
{
    // set the background color to PANTONE Spun Sugar
    glClearColor(0.722, 0.875, 0.925);
    glClear(GL_COLOR_BUFFER_BIT);

    // set the pen color to PANTONE True Red
    glColor3f(0.749, 0.098, 0.196);
    draw_big_fish();

    glFlush();
}

// Keyboard handler
// Sets the gravity constant to 5.9 if the 'I' key
// is pressed
// Sets the gravity constant to 5.3 if the 'M' key
// is pressed
// No longer checks for 'I' or 'M' if the gravity
// constant has been set, based on gravitySet flag
// Displaces the spacecraft right by 4 units if
// the 'J' key is pressed
// Displaces the spacecraft left by 4 units if
// the 'H' key is pressed
// Displaces the spacecraft up by 5 units if
// the 'U' key is pressed
// unsigned char key: key that has been pressed
// int x: x value of the mouse
// int y: y value of the mouse
void key_pressed(unsigned char key, int x, int y)
{
    // checks boolean flag that is set to true once 'I' or 'M' have been pressed
    // does not allow users to move the spacecraft once it has reached the red line
    if (gravitySet && y_axis > 25)
    {
        if ((key == 71) || (key == 104))    // 'J' or 'j'
        {
            translate_x -= 4.0; // move left
        }
        else if ((key == 74) || (key == 106))   // 'H' or 'h'
        {
            translate_x += 4.0; // move right
        }
        else if (((key == 85) || (key == 117)) && (fuel > 0)) // 'U' or 'u'
        {
            y_axis += 5; // move up
            fuel -= 5;  // decrease the fuel level by 5
        }
        glutPostRedisplay();    // redraw the scene
    }
    else
    {
        if ((key == 73) || (key == 105))    // 'I' or 'i'
        {
            gravity = ioGravity;
            gravitySet = true;
            glutTimerFunc(50, spacecraft_animation, 0);
        }
        else if ((key == 77) || (key == 109)) // 'M' or 'm'
        {
            gravity = moonGravity;
            gravitySet = true;
            glutTimerFunc(50, spacecraft_animation, 0);
        }
    }
}


#define canvas_Width 800
#define canvas_Height 800
char canvas_Name[] = "Fish Tank Simulation";

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glutDisplayFunc(display_func);
    glutKeyboardFunc(key_pressed);

    glutMainLoop();
    return 0;
}
