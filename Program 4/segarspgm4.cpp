// Graphics Pgm 4 for Bailee Segars
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

float big_fish_x = 0.0;     // initializes the x value for the center of the octahedron associated with the big fish
bool swimming = true;       // dictates whether or not the scene should be redrawn. Set to false when 'Q' is pressed
bool init_tank = true;      // true only the first time the scene is drawn. Calls the first instance of the timer handler
bool swim_left = true;      // set to true when theta is 0. Starts as true because the fish is initially facing left
bool swim_right = false;    // set to true when theta is 180
int theta = 0;              // initialize theta to 0 because the fish is facing left

// Draws the big fish
void draw_big_fish()
{
    // for matrix transformations
    glMatrixMode(GL_MODELVIEW);

    // push the matrix to transform the fish body
    glPushMatrix();
    glTranslatef(big_fish_x, 0.0, -400.0);
    glRotatef(theta, 0.0, 1.0, 0.0);
    glScalef(75.0, 25.0, 12.5);     // scale/2.0 because we want to scale the entire body, not individual edges
    glutWireOctahedron();
    glPopMatrix();

    // push the matrix to transform the fish tail
    glPushMatrix();
    glTranslatef(big_fish_x, 0.0, -400.0);
    glRotatef(theta, 0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(75.0, 0.0, 0.0);     // z axis is 0.0 because of translating to -400.0 on line 52
        glVertex3f(92.32, -10.0, 0.0);  // calculated triangle size based on width = 7.0
        glVertex3f(92.32, 10.0, 0.0);
    glEnd();
    glPopMatrix();
}

// Draws the little fish
void draw_little_fish()
{
    // for matrix transformations
    glMatrixMode(GL_MODELVIEW);

    // push the matrix to transform the fish body
    glPushMatrix();
    glTranslatef(-325.0, -350.0, -400.0);
    glScalef(25.0, 10.0, 5.0);
    glutWireOctahedron();
    glPopMatrix();

    // draw the triangle for the fish tail
    // because the little fish does not move, it does not need to be transformed
    glBegin(GL_LINE_LOOP);
        glVertex3f(-300.0, -350.0, -400.0);     // since the tail is outside of the matrix we translated in, z axis is -400.0
        glVertex3f(-293.94, -353.50, -400.0);
        glVertex3f(-293.94, -346.50, -400.0);
    glEnd();
}

// Draws the cactus decoration
void draw_cactus()
{
    // main section
    glBegin(GL_LINE_LOOP);
        glVertex3f(50.0, -400.0, -400.0);   // bottom left vertex
        glVertex3f(100.0, -400.0, -400.0);  // bottom right vertex
        glVertex3f(100.0, -225.0, -350.0);  // top right vertex
        glVertex3f(50.0, -225.0, -350.0);   // top left vertex
    glEnd();

    // left horizontal section
    glBegin(GL_LINE_LOOP);
        glVertex3f(50.0, -322.5, -400.0);   // bottom right vertex
        glVertex3f(50.0, -302.5, -350.0);   // top right vertex
        glVertex3f(0.0, -302.5, -400.0);    // top left vertex
        glVertex3f(0.0, -322.5, -350.0);    // bottom left vertex
    glEnd();

    // left vertical section
    glBegin(GL_LINE_LOOP);
        glVertex3f(0.0, -302.5, -400.0);    // bottom left vertex
        glVertex3f(12.0, -302.5, -400.0);   // bottom right vertex
        glVertex3f(12.0, -242.5, -350.0);   // top right vertex
        glVertex3f(0.0, -242.5, -350.0);    // top left vertex
    glEnd();

    // right horizontal section
    glBegin(GL_LINE_LOOP);
        glVertex3f(100.0, -293.33, -400.0); // bottom left vertex
        glVertex3f(150.0, -293.33, -400.0); // bottom right vertex
        glVertex3f(150.0, -273.33, -350.0); // top right vertex
        glVertex3f(100.0, -273.33, -350.0); // top left vertex
    glEnd();

    // right vertical section
    glBegin(GL_LINE_LOOP);
        glVertex3f(150.0, -273.33, -400.0); // bottom right vertex
        glVertex3f(150.0, -213.33, -350.0); // top right vertex
        glVertex3f(138.0, -213.33, -400.0); // top left vertex
        glVertex3f(138.0, -273.33, -350.0); // bottom left vertex
    glEnd();
}

// Keyboard handler
// Sets the boolean to false if the 'Q' or 'q' key
// is pressed so the scene does not continue to be redrawn
// unsigned char key: key that has been pressed
// int x: x value of the mouse
// int y: y value of the mouse
void key_pressed(unsigned char key, int x, int y)
{
    if ((key == 81) or (key == 113))
    {
        swimming = false;
    }
}


// Timer handler
// Redraws the scene with glutPostRedisplay()
// to show the big fish's updated position
// if the boolean 'swimming' is true.
// There are 1000 ms in a second, so
// glutTimerFunc needs to be called after
// 50 ms to be called 20 times per second
// int id: id to be used for the timer handler
void big_fish_animation(int id)
{
    if (swimming)
    {
        glutPostRedisplay();
        glutTimerFunc(50, big_fish_animation, 1);
    }

}

// Display event handler
// Redraws the screen every time glutPostRedisplay() is called
// Sets the colors for the background and each object, then calls
// the functions to draw the objects in the scene
void display_func()
{
    // set the background color to PANTONE Spun Sugar
    glClearColor(0.722, 0.875, 0.925, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // sets the projection of the world region to be -400 to 400 in both x and y
    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400.0, 400.0, -400.0, 400.0, 100.0, 900.0);

    // set the pen color to PANTONE True Red
    glColor3f(0.749, 0.098, 0.196);
    draw_big_fish();

    // set the pen color to PANTONE Tangelo
    glColor3f(1.0, 0.494, 0.015);
    draw_little_fish();

    // sets the pen color to dark green
    glColor3f(0.180, 0.376, 0.129);
    draw_cactus();

    glMatrixMode(GL_PROJECTION);

    if (init_tank)  // if this is the first time the display handler is called
    {
        init_tank = false;
        glutTimerFunc(50, big_fish_animation, 0);
    }

    if (swim_left)  // swim_left is initialized to true. Also returns true when theta is 0
    {
        if ((big_fish_x - 75.0) > -396.0)   // if the nose is more than 4 pixels away from the edge
        {
            theta = 0;      // ensure there is no rotation
            big_fish_x -= 5.0;  // move to the left 5 units
        }
        else    // if the nose is less than 4 pixels away from the edge
        {
            if (theta <= 175)   // if theta is less than 180, then there needs to be more rotations done
            {
                theta += 5; // increment the degrees used in the rotation matrix
            }
            else    // if theta is 180
            {
                swim_left = false;  // can only swim left if theta is 0
                swim_right = true;  // theta is 180, so now go to the right
            }
        }
    }
    else if (swim_right)    // if the fish is swimming to the right (theta is 180)
    {
        if ((big_fish_x + 75.0) < 396.0)    // if the nose of the fish is more than 4 pixels away from the edge
        {
            theta = 180;    // ensure there is no rotation
            big_fish_x += 5.0;  // move to the right 5 units
        }
        else    // if the nose is less than 4 pixels away from the edge
        {
            if (theta >= 0) // if theta is above 0, then there needs to be more rotations done
            {
                theta -= 5; // decrement the degrees used in the rotation matrix
            }
            else
            {
                swim_right = false; // theta is 0, so the fish can't swim to the right
                swim_left = true;   // swim to the left
            }
        }
    }
    glutSwapBuffers();  // swaps the buffers to show the fish's updated position
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
