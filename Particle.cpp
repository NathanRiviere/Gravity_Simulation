#include "Particle.h"


particle::particle(float x, float y, float radius, int mass): pos_x(x), pos_y(y), radius(radius), mass(mass)
{
	vel_x_ = vel_y_ = acl_x_ = acl_y_ = 0;
}


particle::~particle()
{
}
