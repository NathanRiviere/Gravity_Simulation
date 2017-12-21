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
				float x_origin, y_origin;
				int x_f, y_f, x_c, y_c;
				find_mass_centers(x, y, &x_origin, &y_origin, &x_f, &y_f, &x_c, &y_c);

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
				add_space_curvature(x_origin, y_origin, MASS);

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

void field::update_particles()
{
	for(auto &n : particles_)
	{
		// update postion from velocity
		std::cout << "(PRE)  x: " << n.pos_x << " y: " << n.pos_y << std::endl;
		n.pos_x += n.vel_x_;
		n.pos_y += n.vel_y_;
		std::cout << "(POST)  x: " << n.pos_x << " y: " << n.pos_y << std::endl;

		// update velocity from acceleration

		n.vel_x_ += n.acl_x_;
		n.vel_y_ += n.acl_y_;

		// update acceleration from curvature




	}


}

void field::find_mass_centers(int x, int y, float *x_origin, float *y_origin, int *xf, int *yf, int *xc, int *yc)
{
	*xf = (int)std::floor<int>(x / (2 * RADIUS));
	*yf = (int)std::floor<int>(y / (2 * RADIUS));
	*xc = (int)std::ceil<int>(x / (2 * RADIUS));
	*yc = (int)std::ceil<int>(y / (2 * RADIUS));

	*x_origin = ((x / (2 * RADIUS)) - *xf) * 10;
	*y_origin = ((y / (2 * RADIUS)) - *yf) * 10;

	if (*x_origin == 0)
	{
		// x stays the same
	}
	else if (*x_origin < 5)
	{
		*x_origin = *xf;
	}
	else
	{
		*x_origin = *xc;
	}

	if (*y_origin == 0)
	{
		// y stays the same
	}
	else if (*y_origin < 5)
	{
		*y_origin = *yf;
	}
	else
	{
		*y_origin = *yc;
	}
}
