#pragma once
#include "field.h"
#include <ctime>
#include <iostream>

void display();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void tick(int i);

field *space = nullptr;


int main(int argc, char **argv)
{
	const int window_size = 500;

	space = new field(window_size);

	/*                  CREATE WINDOW                                                   */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(window_size, window_size);
	glutInitWindowPosition(50, 50);
	auto win = glutCreateWindow("Gravity_Simulation Application");

	/*                  SET UP MATRICES													 */
	glClearColor(0, 0,  0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_size, window_size, 0, 0, 1);
	

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	tick(0);

	glutMainLoop();

	delete space;

}

void display()
{
	space->display();
}

void mouse(int button, int state, int x, int y)
{
	space->spawn_particle(button, state, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
	space->keyboard_input(key, x, y);
}

void tick(int i)
{
    space->update_particles();
	glutTimerFunc(33, tick, 0);
}