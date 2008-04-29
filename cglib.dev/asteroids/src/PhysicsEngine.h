#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "PhysicsObject.h"

namespace  asteroids{
	const double PI4  = 4.0*atan(1.0);
	class PhysicsObject;

	class PhysicsEngine{
	public:
		cg::Vector2d _position;
		cg::Vector2d _velocity;
		double _acelFactor;
		cg::Vector2d _minVelocity, _acceleration;
		bool _withRotation, _withMinVelocity, _accelerating;
		double _rotFactor, _rotationDeg, _rotationRad;
		bool _rotating;
		double _universeWidth, _universeHeight;
		double _collisionRadius;
		cg::Vector2d _collisionCenter;
	public:
		PhysicsEngine();
		PhysicsEngine(cg::Vector2d velocity,cg::Vector2d position);
		virtual ~PhysicsEngine();
		void startAcceleration(double factor, bool withRotation);
		void startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity);
		void stopAcceleration();
		void accelerate(double factor, bool withRotation);
		void accelerate(double factor, bool withRotation, cg::Vector2d minVelocity);
		cg::Vector2d getAcceleration() const;
		cg::Vector2d getVelocity() const;
		cg::Vector2d getNormalizedVelocity() const;
		cg::Vector2d getPosition() const;
		void setUniverseDimensions(int width, int height);
		void setVelocity(cg::Vector2d);
		void setPosition(cg::Vector2d);
		void startRotator(double factor);
		void stopRotator();
		double getRotation() const;
		double getRotation(bool inDegrees) const;
		void rotate(double factor);
		void update(double elapsed_millis);
		cg::Vector2d getUniverseDimensions(void);
		double randomBetween(double min, double max);
		double getCollisionRadius();
		cg::Vector2d getCollisionCenter();
		void setCollisionRadius(double collisionRadius);
		void setCollisionCenter(cg::Vector2d collisionCenter);
		bool collidesWith(PhysicsObject *pobject);
	};
}

#endif
