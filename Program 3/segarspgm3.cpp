// Graphics Pgm 3 for Bailee Segars
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
    // the timer handler. When the letter 'M' or 'I' is pressed, the
    // keyboard handler sets gravity to the corresponding gravity constant
    // and starts a timer event. When the letter 'H' or 'J' is pressed,
    // the keyboard handler shifts the x value of the spacecraft
    // and triggers a display event to redraw the scene.
    // The timer handler calls spacecraft_animation,
    // which triggers a display event after 50ms to redraw
    // the scene with the spacecraft in its new position 20 times per second.
    // The display handler redraws the scene until the program
    // is closed.

float moonGravity = 5.3;
float ioGravity = 5.9;
float gravity = 0.0;
float velTime = 0.0;
float translate_x = 400.0;
float translate_y = 0.0;
int y_axis = 582;
int fuel = 200;
char buffer[10];

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

// Prints the prompt string to choose gravity constant
// Sets the font color state and the position
// before calling the function to print the string
 void display_starting_text()
 {
     glColor3f(0.0, 0.0, 0.0);
     glRasterPos3f(300.5, 285.5, -50.0);
     write_bitmap_string(GLUT_BITMAP_TIMES_ROMAN_24, "Press M or I to Start");
 }

// Prints the string telling the user they won
// Sets the font color state and the position
// before calling the function to print the string
  void display_winning_text()
 {
     glColor3f(0.0, 0.0, 0.0);
     glRasterPos3f(346.5, 285.5, -50.0);
     write_bitmap_string(GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN");
 }

// Prints a string with the remaining fuel level
// Sets the font color state and the position
// before calling the function to print the string
// Uses sprintf to display the numeric fuel value as a string
 void display_fuel_text()
 {
     sprintf(buffer, "Fuel: %d", fuel);
     glColor3f(0.0, 0.0, 0.0);
     glRasterPos3f(700.0, 575.0, -50.0);
     write_bitmap_string(GLUT_BITMAP_TIMES_ROMAN_24, buffer);
 }

// Draws the spacecraft
void draw_spacecraft()
{
    // checks if M or I have been pressed yet
    if (gravitySet)
    {
        // if y_axis is above 25, then the tip is above the red line
        if (y_axis > 25)
        {
            y_axis = (int)(translate_y*velTime - (gravity*velTime*velTime) + 582.33);   // gravity formula
            glPushMatrix();
            glTranslatef(translate_x, y_axis, 0.0);
            glScalef(17.67, 17.67, 17.67);
            glutWireOctahedron();
            glPopMatrix();
        }
        // if tip is within the landing zone
        else if ((y_axis < 32) && (translate_x >= 37.33) && (translate_x <= 52.67))
        {
            glPushMatrix();
            glTranslatef(45.0, 24.67, 0.0); // redraw it to be in the center
            glScalef(17.67, 17.67, 17.67);
            glutWireOctahedron();
            glPopMatrix();
            display_winning_text();         // display "YOU WON"
        }
        // if the tip is at the red line, but not in the landing zone
        else
        {
            glPushMatrix();
            glTranslatef(translate_x, 24.67, 0.0);  // continue to redraw in the same spot
            glScalef(17.67, 17.67, 17.67);
            glutWireOctahedron();
            glPopMatrix();
        }
    }
    // the user has not pressed M or I yet
    else
    {
        display_starting_text();
        glColor3f(0.0, 0.46, 0.78); // set the pen color to UAH blue
        glPushMatrix();
        glTranslatef(400.0, 582.33, -50.0);
        glScalef(17.67, 17.67, 17.67);
        glutWireOctahedron();
        glPopMatrix();
    }
}

// Timer handler
// Redraws the scene with glutPostRedisplay()
// to show the spacecraft's updated placement
// There are 1000 ms in a second, so
// glutTimerFunc needs to be called after
// 50 ms to update every 20 seconds
// velTime is incremented by 0.05 so the
// spacecraft's falling rate is updated 20
// times per second
// int id: id to be used for the timer handler
void spacecraft_animation(int id)
{
    velTime += 0.05;
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
    // set the background color to yellow
    glClearColor(1.0, 0.87, 0.13, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_spacecraft();
    display_fuel_text();

    // set the pen color to red
    glColor3f(1.0, 0.0, 0.0);

    // draw the horizontal line
    glBegin(GL_LINES);
        glVertex3f(0.0, 7.0, -50.0);
        glVertex3f(800.0, 7.0, -50.0);
    glEnd();

    // set the pen color to UAH blue
    glColor3f(0.0, 0.46, 0.78);

    // draw the landing zone
    glBegin(GL_LINE_LOOP);
        glVertex3f(25.0, 3.5, -50.0);   // bottom left vertex
        glVertex3f(25.0, 13.5, -50.0);  // top left vertex

        glVertex3f(25.0, 13.5, -10.0);  // top left vertex
        glVertex3f(35.0, 13.5, -50.0);  // top middle vertex

        glVertex3f(35.0, 13.5, -50.0);  // left middle vertex
        glVertex3f(45.0, 7.0, -50.0);   // chevron point vertex

        glVertex3f(45.0, 7.0, -50.0);   // chevron point vertex
        glVertex3f(55.0, 13.5, -50.0);  // right middle vertex

        glVertex3f(55.0, 13.5, -50.0);  // right middle vertex
        glVertex3f(65.0, 13.5, -50.0);  // top right vertex

        glVertex3f(65.0, 13.5, -50.0);  // top right vertex
        glVertex3f(65.0, 3.5, -50.0);   // bottom right vertex
    glEnd();

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
    // boolean flag that is set to true once 'I' or 'M' have been pressed
    if (gravitySet)
    {
        if ((key == 71) || (key == 104))    // 'J' or 'j'
        {
            translate_x -= 4.0; // move left
            translate_y -= 0.0;
        }
        else if ((key == 74) || (key == 106))   // 'H' or 'h'
        {
            translate_x += 4.0; // move right
            translate_y -= 0.0;
        }
        else if (((key == 85) || (key == 117)) && (fuel > 0)) // 'U' or 'u'
        {
            translate_x -= 0.0;
            translate_y += 5.0; // move up
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
#define canvas_Height 600
char canvas_Name[] = "Spacecraft Landing";

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glutDisplayFunc(display_func);
    glutKeyboardFunc(key_pressed);

    glutMainLoop();
    return 0;
}
