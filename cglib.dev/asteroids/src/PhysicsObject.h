#pragma once
#ifndef PHYSICS_OBJ_H
#define PHYSICS_OBJ_H
#pragma message("PhysicsObject is included")
#include "cg/cg.h"
#include "PhysicsEngine.h"


namespace asteroids {
	class PhysicsEngine;

	class PhysicsObject 
	{
	public:
		PhysicsObject();
		PhysicsObject(double mass);
		virtual ~PhysicsObject();

		virtual void accelerate(double factor, bool withRotation);
		virtual void accelerate(double factor, bool withRotation, cg::Vector2d minVelocity);
		virtual void rotate(double factor);
		virtual void startRotation(double factor);
		virtual void stopRotation();
		virtual void startAcceleration(double factor, bool withRotation);
		virtual void startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity);
		virtual void stopAcceleration();
		virtual void setVelocity(cg::Vector2d velocity);
		virtual cg::Vector2d getNormalizedVelocity() const;
		virtual cg::Vector2d getVelocity() const;
		virtual double getRotation() const;
		virtual double getRotation(bool inDegrees) const;
		virtual void setRotation(double radiansRotation);
		virtual cg::Vector2d getUniverseDimensions(void);
		virtual void setPosition(cg::Vector2d position);
		virtual cg::Vector2d getPosition() const;
		virtual cg::Vector2d getAcceleration() const; 	
		virtual bool collidesWith(PhysicsObject *pobject);
		virtual double getCollisionRadius();
		virtual cg::Vector2d getCollisionCenter();
		virtual void setCollisionRadius(double collisionRadius);
		virtual void setCollisionCenter(cg::Vector2d collisionCenter);
		virtual void setUniverseDimensions(int width, int height);
		virtual void update(unsigned long elapsed_millis);
		virtual double getMass(void);
		virtual void setMass(double mass);
		virtual void calculateCollision(PhysicsObject *pobject);
		virtual void stepBack(void);
		virtual bool penetrates(PhysicsObject *pobject);
		virtual void setRotationFactor(double factor);
		virtual double getRotationFactor(void);
		
	private:
		PhysicsEngine * _physics;
	};

}

#endif