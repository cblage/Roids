#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>

namespace  asteroids{
	const double PI4  = 4.0*atan(1.0);
	
	class PhysicsEngine{
	private:
		//asteroid.h
		cg::Vector2d _position;
		cg::Vector2d _velocity;
		//asteroidaccelerator.h
		double _acelFactor;
		cg::Vector2d _minVelocity, _acceleration;
		bool _withRotation, _withMinVelocity, _accelerating;
		//Asteroid Engine.H
		//ASteroid Rotator.H
		double _rotFactor, _rotationDeg, _rotationRad;
		bool _rotating;
		double _universeWidth, _universeHeight;
	public:
		PhysicsEngine();
		PhysicsEngine(cg::Vector2d velocity,cg::Vector2d position);
		virtual ~PhysicsEngine();
		//Asteroid Acelerator
		void startAcceleration(double factor, bool withRotation);
		void startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity);
		void stopAcceleration();
		void accelerate(double factor, bool withRotation);
		void accelerate(double factor, bool withRotation, cg::Vector2d minVelocity);
		cg::Vector2d getAcceleration() const;
		cg::Vector2d getVelocity() const;
		cg::Vector2d getNormalizedVelocity() const;
		//position
		cg::Vector2d getPosition() const;
		void setUniverseDimensions(int width, int height);
		void setVelocity(cg::Vector2d);
		void setPosition(cg::Vector2d);
		

		//asteroid Rotator.H
		void startRotator(double factor);
		void stopRotator();
		double getRotation() const;
		double getRotation(bool inDegrees) const;
		void rotate(double factor);
		
		void update(double elapsed_seconds);

		double randomBetween(double min, double max);
	};
}

#endif
