// Graphics Pgm 3 for Bailee Segars
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup-2025.h"

// Author: Bailee Segars
// CS 445-01 SP25
// Architecture:
    // GLUT event-driven generation of a wintry scene.
    // The canvas is named Snowflake Scene and is produced
    // via the display event handler, which is in display_func.
    // display_func calls a display list with a group of commands
    // to draw the snowman each time the scene is redrawn.
    // The keyboard press is handled via the keyboard
    // event handler, which is in key_pressed.
    // The mouse button click is handled via the mouse handler,
    // which is in mouse_CB.
    // Display events are triggered by the keyboard handler and
    // the timer handler. When the letter 'b' is pressed, the
    // keyboard handler shifts the x value of the snowflakes
    // and triggers a display event to redraw the scene
    // The mouse handler makes the first call to the
    // timer handler when a button is pressed.
    // The timer handler calls snowflake_animation,
    // which triggers a display event after 20ms to redraw
    // the scene with the snowflakes in their new positions.
    // The display handler redraws the scene until the program
    // is closed.

float moonGravity = 5.3;
float ioGravity = 5.9;
float translate_x = 0.0;
float translate_y = 0.0;
int fuel = 200;

// flag to determine if the text should be rendered
bool text = true;

// flag to determine if the gravity has been set yet
bool gravitySet = false;

// Prints a string character by character
// to the screen using a bitmap
// void *font: GLUT supported font
// char *string: string to be printed on the screen
void write_bitmap_string(void *font, char *string)
{
    char *c;
	for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

// Sets the font color state and the position
// before calling the function to print the string
// void display_text()
// {
//     glColor3f(1.0, 1.0, 1.0);
//     glRasterPos3f(164.5, 285.5, -5.0);
//     write_bitmap_string(GLUT_BITMAP_TIMES_ROMAN_24, "Any Mouse Click Will Start");
// }

// Draws the first (leftmost) snowflake
// float x_axis: offset for shifting the snowflake on the x axis
// The first snowflake's offset is 0.0
void draw_spacecraft()
{
    glPushMatrix();
    glTranslatef(translate_x, translate_y, 0.0);
    glColor3f(0.0, 0.46, 0.78);
    glutWireOctahedron();
    glPopMatrix();
}

// Display event handler
// Redraws the screen every time glutPostRedisplay() is called
// Determines if the text should be displayed based on the boolean flag value
// Calls the display list to redraw the snowman each time the scene is redrawn
// Makes adjustments to the x and y values for the first and second snowflakes
// Each snowflake's y axis is decremented by 2.85, then the x axis incremented
// by 2.0, and then the y axis is decremented by 2.85 again
// The change in the y axis, combined with the timer function being called after 20ms,
// allows the snowflake to appear to be moving to the user
void display_func()
{
    // set the background color to yellow
    glClearColor(1.0, 0.87, 0.13, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_spacecraft();

    // set the color to red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(-35.35, -32.56, 0.0); //582.33-7 = 575.33/17.67
        glVertex3f(35.35, -32.56, 0.0);
    glEnd();

    glFlush();
}

// Simulates a snow blower by displacing the snowflakes
// right 4 units if the 'b' key is pressed
// unsigned char key: key that has been pressed
// int x: x value of the mouse
// int y: y value of the mouse
void key_pressed(unsigned char key, int x, int y)
{
    if (gravitySet)
    {
        if ((key == 71) || (key == 104))
        {
            translate_x -= 0.16;
            translate_y -= 0.0;
        }
        else if ((key == 74) || (key == 106))
        {
            translate_x += 0.16;
            translate_y -= 0.0;
        }
        else if (((key == 85) || (key == 117)) && (fuel > 0))
        {
            translate_x -= 0.0;
            translate_y += 0.20;
            fuel -= 5;
        }
        glutPostRedisplay();
    }
    else
    {
        if ((key == 73) || (key == 105))
        {
            //gravity = ioGravity;
        }
        else if ((key == 77) || (key == 109))
        {
            //gravity = moonGravity;
        }
        gravitySet = true;
    }
}


#define canvas_Width 800
#define canvas_Height 600
char canvas_Name[] = "Spacecraft Landing";

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glTranslatef(400.0, 582.33, -50.0);
    glScalef(17.67, 17.67, 17.67);

    glutDisplayFunc(display_func);
    glutKeyboardFunc(key_pressed);

    glutMainLoop();
    return 0;
}
