#ifndef ASTEROID_ACCELERATOR_H
#define ASTEROID_ACCELERATOR_H

#include "cg/cg.h"
#include "AsteroidEngine.h"

namespace asteroids {
	class Asteroid;
	class AsteroidAccelerator : public AsteroidEngine
	{
	public:
		AsteroidAccelerator(Asteroid * asteroid);
		virtual ~AsteroidAccelerator(void);
		void start(double factor, bool withRotation);
		void start(double factor, bool withRotation, cg::Vector2d minVelocity);
		void stop();
		void update(double elapsed_seconds);
		void accelerate(double factor, bool withRotation);
		void accelerate(double factor, bool withRotation, cg::Vector2d minVelocity);
		cg::Vector2d getAcceleration() const;

	private: 
		double _factor;
		cg::Vector2d _minVelocity, _acceleration;
		bool _withRotation, _withMinVelocity, _accelerating;
	};
}
#endif
