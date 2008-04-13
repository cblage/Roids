#ifndef ASTEROID_ROTATOR_H
#define ASTEROID_ROTATOR_H

#include "cg/cg.h"
#include "AsteroidEngine.h"

namespace asteroids {
	const double PI2  = 4.0*atan(1.0);
	class Asteroid;
	class AsteroidRotator : public AsteroidEngine
	{
	public:
		AsteroidRotator(Asteroid * asteroid);
		virtual ~AsteroidRotator(void);
		void start(double factor);
		void stop();
		void update(double elapsed_seconds);
		double getRotation() const;
		double getRotation(bool inDegrees) const;
		void rotate(double factor);
		
	private: 
		double _factor, _rotationDeg, _rotationRad;
		bool _rotating;
	};
}
#endif
