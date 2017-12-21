#include "field.h"
#include <chrono>
#include <iostream>

#define M_PI 3.14159265
#define RADIUS 5
#define MASS 2
#define DEBUG 0

field::field(int window_size)
{

	while(window_size % (RADIUS * 2) != 0)
	{
		window_size++;
	}

	const int cell_amt = window_size / (RADIUS * 2);
	cells_ = new cell*[cell_amt];
	for(int i = 0; i < cell_amt; ++i)
		cells_[i] = new cell[cell_amt];

	window_size_ = window_size;
}


field::~field()
{
}

void field::spawn_particle(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) break;
			else
			{
				int x_f = (int)std::floor<int>(x / (2 * RADIUS));
				int y_f = (int)std::floor<int>(y / (2 * RADIUS));
				int x_c = (int)std::ceil<int>(x / (2 * RADIUS));
				int y_c = (int)std::ceil<int>(y / (2 * RADIUS));

				float x_orgin = ((x / (2 * RADIUS)) - x_f) * 10;
				float y_orgin = ((y / (2 * RADIUS)) - y_f) * 10;

				if(x_orgin == 0)
				{
					// x stays the same
				}  else if (x_orgin < 5)
				{
					x_orgin = x_f;
				} else
				{
					x_orgin = x_c;
				}

				if (y_orgin == 0)
				{
					// y stays the same
				}
				else if (y_orgin < 5)
				{
					y_orgin = y_f;
				}
				else
				{
					y_orgin = y_c;
				}


				if (cells_[x_f][y_f].is_occupied | cells_[x_f][y_c].is_occupied | 
					cells_[x_c][y_f].is_occupied | cells_[x_c][y_c].is_occupied) {
#if DEBUG == 1 
					std::cout << "Space occupied" << std::endl;
				
#endif
					break;
				}

				particles_.emplace_back(x, y, RADIUS, MASS);

#if DEBUG == 1 
				std::cout << "Particle created" << std::endl;
				
#endif
				add_space_curvature(x_orgin, y_orgin, MASS);

				cells_[x_f][y_f].is_occupied = cells_[x_f][y_c].is_occupied =
					cells_[x_c][y_f].is_occupied = cells_[x_c][y_c].is_occupied = true;

				break;
			}
		case GLUT_RIGHT_BUTTON:
			break;
	}	
}

void field::display()
{
	move_particles();

	glClear(GL_COLOR_BUFFER_BIT);


	for(auto &p : particles_)
	{
		float pos_x = p.pos_x;
		float pos_y = p.pos_y;
		float radius = p.radius;


		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		for (float a = 0; a < 2 * M_PI; a += 0.1) {
			glVertex2f(radius * cos(a) + pos_x, radius * sin(a) + pos_y);
		}
		glEnd();
	}

	glFlush();
}

void field::keyboard_input(unsigned char key, int x, int y)
{
	
}

void field::add_space_curvature(int x, int y, int mass)
{

	for (int grow = 1; grow < 8; grow++)
	{
		for(int i = -1 * grow + y ; i <= grow + y; i++)
		{
			for (int j = -1 * grow + x; j <= grow + x; j++)
			{
				if (i < 0 | i > window_size_ - 1) break;
				if (j < 0) continue;
				if (j > window_size_ - 1) break;

				if (i == 0 && j == 0) cells_[i][j].gravity = 0;
				else
				{
					cells_[i][j].gravity += mass / grow;
#if DEBUG == 1 
					std::cout << "gravity at (" << i << ", " << j << ") is " << (float) mass / grow << std::endl;
					
#endif
				} 
			}
		}
	}
}

void field::move_particles()
{
	
}
