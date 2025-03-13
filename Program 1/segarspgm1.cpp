// Graphics Pgm 1 for Bailee Segars
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-2025.h"
#include <iostream>

// Author: Bailee Segars
// CS 445-01 SP25
// Architecture:
    // GLUT event-driven generation of a canvas with a snowman
    // and a snowflake on it. Once a key has been pressed while
    // the canvas is in focus, the snowflake moves in a straight
    // line down the screen.
    // The canvas is named Snowflake Scene and is produced via 
    // the display event handler, which is in display_func.
    // The keyboard press is handled via the keyboard event
    // handler, which is in key_pressed.
    // The snowflake animation is handled by decreasing the 
    // snowflake's y-axis position and redrawing the screen
    // at regular intervals, which is in snowflake_animation.


// initial starting y axis is at the top of the canvas
int snowflake_y_axis = 600;

// display event handler
// draws the lines for each box to make up the snowman, specified by each vertex
// draws the snowflake with three lines, sepcified by each vertex
// snowflake_y_axis is modified in snowflake_animation
void display_func()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
        
    // Set the color to white
    glColor3f(1.0, 1.0, 1.0);

    // snowman and snowflake
    glBegin(GL_LINES);
        // snowman

        // bottom box
        // left side
        glVertex3i(245, 0, -5); // bottom left
        glVertex3i(245, 150, -5); // top left

        // top
        glVertex3i(245, 150, -5); // top left
        glVertex3i(395, 150, -5); // top right

        // right side
        glVertex3i(395, 0, -5); // bottom right
        glVertex3i(395, 150, -5); // top right

        // bottom
        glVertex3i(245, 0, -5); // bottom left
        glVertex3i(395, 0, -5); // bottom right

        // middle box
        // left side
        glVertex3i(265, 150, -5); // bottom left
        glVertex3i(265, 260, -5); // top left

        // top
        glVertex3i(265, 260, -5); // top left
        glVertex3i(375, 260, -5); // top right

        // right side
        glVertex3i(375, 150, -5); // bottom right
        glVertex3i(375, 260, -5); // top right

        // bottom
        glVertex3i(265, 150, -5); // bottom left
        glVertex3i(375, 150, -5); // bottm right

        // top box
        // left side
        glVertex3i(290, 260, -5); // bottom left
        glVertex3i(290, 320, -5); // top left

        // top
        glVertex3i(290, 320, -5); // top left
        glVertex3i(350, 320, -5); // top right

        // right side
        glVertex3i(350, 260, -5); // bottom right
        glVertex3i(350, 320, -5); // top right

        // bottom
        glVertex3i(290, 260, -5); // bottom left
        glVertex3i(350, 260, -5); // bottom right

        // snowflake
        // left diagonal line
        glVertex3i(70, snowflake_y_axis, -5); // top left
        glVertex3i(121.9615242, snowflake_y_axis-60, -5); // bottom right

        // middle vertical line
        glVertex3i(95.98076211, snowflake_y_axis, -5); // top middle
        glVertex3i(95.98076211, snowflake_y_axis-60, -5); // bottom middle

        // right diagonal line
        glVertex3i(121.9615242, snowflake_y_axis, -5); // top right
        glVertex3i(70, snowflake_y_axis-60, -5); // bottom left
    glEnd();

    glFlush();
}

// handles the snowflake movement
// int id: id to be used for the timer function
// checks the y axis of the snowflake. If it is not at the bottom, move the y axis down by 5 units
// redraws the display with the updated snowflake placement
void snowflake_animation(int id)
{
    if (snowflake_y_axis > 60) {
        snowflake_y_axis -= 5;
        glutTimerFunc(30, snowflake_animation, 1);
        glutPostRedisplay();
    }
}

// handles if any key has been pressed
// unsigned char key: key that has been pressed
// int x: x value of the mouse
// int y: y value of the mouse
void key_pressed(unsigned char key, int x, int y)
{
    glutTimerFunc(30, snowflake_animation, 0);
}


#define canvas_Width 600
#define canvas_Height 600
char canvas_Name[] = "Snowflake Scene";

int main(int argc, char ** argv)
{
    std::cout << "Any Key Click Will Start" << std::endl;
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);
    glutDisplayFunc(display_func);
    glutKeyboardFunc(key_pressed);
    glutMainLoop();
    return 0;
}