// Graphics Pgm 2 for Bailee Segars
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


// initial x and y axes for two snowflakes
// initial y axis is at the top of the canvas
// initial x axis is touching the left edge
// the second snowflake's x axis is offset by the
// parameter passed to draw_snowflake1(float x_axis)
float snowflake_y_axis = 600.0;
float snowflake1_y_axis = 600.0;
float snowflake_x_axis = 0.0;
float snowflake1_x_axis = 0.0;

// flag to determine if the text should be rendered
bool text = true;

// variable used to create a display list
static unsigned int snowman;

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
void display_text()
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(164.5, 285.5, -5.0);
    write_bitmap_string(GLUT_BITMAP_TIMES_ROMAN_24, "Any Mouse Click Will Start");
}

// Uses a display list to draw the snowman
// The snowman is made up of many line segments,
// specified by each vertex
void setup()
{
    snowman = glGenLists(1);

    glNewList(snowman, GL_COMPILE);
        // bottom box of snowman
        glBegin(GL_LINES);
            // left side
            glVertex3i(205, 0, -10); // bottom left
            glVertex3i(205, 150, -10); // top left

            // top
            glVertex3i(205, 150, -10); // top left
            glVertex3i(355, 150, -10); // top right

            // right side
            glVertex3i(355, 0, -10); // bottom right
            glVertex3i(355, 150, -10); // top right

            // bottom
            glVertex3i(205, 0, -10); // bottom left
            glVertex3i(355, 0, -10); // bottom right
        glEnd();

        // middle box of snowman
        glBegin(GL_LINES);
            // left side
            glVertex3i(225, 150, -10); // bottom left
            glVertex3i(225, 260, -10); // top left

            // top
            glVertex3i(225, 260, -10); // top left
            glVertex3i(335, 260, -10); // top right

            // right side
            glVertex3i(335, 150, -10); // bottom right
            glVertex3i(335, 260, -10); // top right

            // bottom
            glVertex3i(225, 150, -10); // bottom left
            glVertex3i(335, 150, -10); // bottom right
        glEnd();

        // top box of snowman
        glBegin(GL_LINES);
            // left side
            glVertex3i(250, 260, -10); // bottom left
            glVertex3i(250, 320, -10); // top left

            // top
            glVertex3i(250, 320, -10); // top left
            glVertex3i(310, 320, -10); // top right

            // right side
            glVertex3i(310, 260, -10); // bottom right
            glVertex3i(310, 320, -10); // top right

            // bottom
            glVertex3i(250, 260, -10); // bottom left
            glVertex3i(310, 260, -10); // bottom right
        glEnd();
    glEndList();
}

// Draws the first (leftmost) snowflake
// float x_axis: offset for shifting the snowflake on the x axis
// The first snowflake's offset is 0.0
void draw_snowflake(float x_axis)
{
    x_axis += snowflake_x_axis;
    glBegin(GL_LINES);
        // left diagonal line
        glVertex3i(x_axis, snowflake_y_axis, -10.0); // top left
        glVertex3i(x_axis+51.96, snowflake_y_axis-51.96, -10.0); // bottom right

        // middle vertical line
        glVertex3i(x_axis, snowflake_y_axis-25.98, -10.0); // top middle
        glVertex3i(x_axis+60.0, snowflake_y_axis-25.98, -10.0); // bottom middle

        // right diagonal line
        glVertex3i(x_axis, snowflake_y_axis-51.96, -10.0); // top right
        glVertex3i(x_axis+51.96, snowflake_y_axis, -10.0); // bottom left
    glEnd();
}

// Draws the second (rightmost) snowflake
// float x_axis: offset for shifting the snowflake on the x axis
// The second snowflake's offset is 100.0
void draw_snowflake1(float x_axis)
{
    x_axis += snowflake1_x_axis;
    glBegin(GL_LINES);
        // left diagonal line
        glVertex3i(x_axis, snowflake1_y_axis, -10.0); // top left
        glVertex3i(x_axis+51.96, snowflake1_y_axis-51.96, -10.0); // bottom right

        // middle vertical line
        glVertex3i(x_axis, snowflake1_y_axis-25.98, -10.0); // top middle
        glVertex3i(x_axis+60.0, snowflake1_y_axis-25.98, -10.0); // bottom middle

        // right diagonal line
        glVertex3i(x_axis, snowflake1_y_axis-51.96, -10.0); // top right
        glVertex3i(x_axis+51.96, snowflake1_y_axis, -10.0); // bottom left
    glEnd();
}

// Redraws the scene with glutPostRedisplay()
// to show the snowflake's updated placement
// int id: id to be used for the timer handler
void snowflake_animation(int id)
{
    glutPostRedisplay();
    glutTimerFunc(20, snowflake_animation, 1);
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
    // set the background color to charcoal gray
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // set the color to white
    glColor3f(1.0, 1.0, 1.0);

    // checks the flag for printing the bitmap text
    if (text)
    {
        display_text();
    }

    // calls the display list to draw the snowman
    glCallList(snowman);

    // draws the first snowflake
    draw_snowflake(0.0);

    // determines if the snowflake should move down, over, down
    // or if it needs to be redrawn at the top of the scene
    if (snowflake_y_axis >= 51.0)
    {
        snowflake_y_axis -= 2.85;
        snowflake_x_axis += 2.0;
        snowflake_y_axis -= 2.85;
    }
    else
    {
        snowflake_y_axis = 600.0;
        snowflake_x_axis = 0.0;
    }

    // the second snowflake is drawn at the top of the scene for the first time when the first snowflake is halfway down the scene.
    // if the first snowflake is above the halfway point, check if the second snowflake is in the bottom half of the scene.
    // the snowflakes have about a half screen difference in their y values.
    if ((snowflake_y_axis <= 351.0 && snowflake1_y_axis >= 51.0) || (snowflake_y_axis >= 351.0 && snowflake1_y_axis <= 351.0 && snowflake1_y_axis >= 51.0))
    {
        draw_snowflake1(100.0); // x_value offset from the first snowflake by 100.0
        snowflake1_y_axis -= 2.85;
        snowflake1_x_axis += 2.0;
        snowflake1_y_axis -= 2.85;
    }
    if (snowflake1_y_axis <= 51)   // redraw the second snowflake at the top of the scene if it has reached the bottom
    {
        snowflake1_y_axis = 600;
        snowflake1_x_axis = 0.0;
    }

    glFlush();
}

// Simulates a snow blower by displacing the snowflakes
// right 4 units if the 'b' key is pressed
// unsigned char key: key that has been pressed
// int x: x value of the mouse
// int y: y value of the mouse
void key_pressed(unsigned char key, int x, int y)
{
    if(key == 98 && snowflake_y_axis >= 251.0 && snowflake_y_axis <= 400.0)
    {
        snowflake_x_axis += 4.0;
    }
    if(key == 98 && snowflake1_y_axis >= 251.0 && snowflake1_y_axis <= 400.0)
    {
        snowflake1_x_axis += 4.0;
    }
}

// Starts the snowflake animation when any mouse button is pressed
// Sets the text flag to false so the string will not be printed when the scene is redrawn
// Unregisters the event handler from the mouse click event so the snowflake is not affected
// by subsequent clicks
// int button: mouse button pressed
// int state: mouse button state - up or down
// int x: cursor x value
// int y: cursor y value
void mouse_CB(int button, int state, int x, int y)
{
    text = false;
    glutTimerFunc(20, snowflake_animation, 0);
    glutMouseFunc(0);
}


#define canvas_Width 600
#define canvas_Height 600
char canvas_Name[] = "Snowflake Scene";

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);
    glutDisplayFunc(display_func);
    glutKeyboardFunc(key_pressed);
    glutMouseFunc(mouse_CB);

    setup();

    glutMainLoop();
    return 0;
}
