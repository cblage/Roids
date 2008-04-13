#ifndef ASTEROID_ENG_H
#define ASTEROID_ENG_H

#include "cg/cg.h"

namespace asteroids {
	class Asteroid;
	
	class AsteroidEngine
	{
	public:
		AsteroidEngine(Asteroid * asteroid) : _asteroid(asteroid) {}
		~AsteroidEngine(void) {}
		virtual void update(double elapsed_seconds) = 0;

	protected:
		Asteroid * _asteroid;
	};
}

#endif