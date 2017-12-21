#pragma once

#include "Particle.h"
#include "gl/freeglut.h"


class field
{
	public:

		explicit field(const int window_size);
		~field();
		void spawn_particle(int button, int state, int x, int y);
		void display();
		void keyboard_input(unsigned char key, int x, int y);
		void add_space_curvature(int x, int y, int mass);
		void update_particles();
		void find_mass_centers(int x, int y, float *x_origin, float *y_origin, int *xf, int *yf, int *xc, int *yc);

	private:

	struct cell
	{
		int length_px;
		float gravity;
		bool is_occupied = false;
	};

	std::vector<particle> particles_;
	cell **cells_;

	int window_size_;

};

