#pragma once
#include <vector>

// radius in pixels

class particle
{
	public:

		const float radius;
		float pos_x;
		float pos_y;
		int mass;

		 particle(float x, float y, float radius, int mass);
		~particle();

	private:

		float vel_x_, vel_y_, acl_x_, acl_y_;

};

