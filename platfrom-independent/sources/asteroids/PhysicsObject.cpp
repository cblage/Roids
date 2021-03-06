/*
 Roids!
 Copyright (C) 2008 Carlos Lage, Tiago Coelho, Eduardo Castanho

 This file is part of Roids!.

 Roids! is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Roids! is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Roids!; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "PhysicsObject.h"
#include "PhysicsEngine.h"

namespace asteroids
{

	PhysicsObject::PhysicsObject()
	{
		_physics = new PhysicsEngine();
	}

	PhysicsObject::PhysicsObject(double mass)
	{
		_physics = new PhysicsEngine(mass);
	}

	PhysicsObject::~PhysicsObject()
	{
		delete (_physics);
	}

	double PhysicsObject::getMass(void)
	{
		return _physics->getMass();
	}

	void PhysicsObject::setMass(double mass)
	{
		_physics->setMass(mass);
	}

	void PhysicsObject::accelerate(double factor, bool withRotation)
	{
		_physics->accelerate(factor, withRotation);
	}

	void PhysicsObject::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity)
	{
		_physics->accelerate(factor, withRotation, minVelocity);
	}

	void PhysicsObject::startAcceleration(double factor, bool withRotation)
	{
		_physics->startAcceleration(factor, withRotation);
	}
	void PhysicsObject::startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity)
	{
		_physics->startAcceleration(factor, withRotation, minVelocity);
	}

	void PhysicsObject::stopAcceleration()
	{
		_physics->stopAcceleration();
	}

	void PhysicsObject::startRotation(double factor)
	{
		_physics->startRotator(factor);
	}

	void PhysicsObject::stopRotation()
	{
		_physics->stopRotator();
	}

	void PhysicsObject::setVelocity(cg::Vector2d velocity)
	{
		_physics->setVelocity(velocity);
	}

	cg::Vector2d PhysicsObject::getVelocity() const
	{
		return _physics->getVelocity();
	}

	cg::Vector2d PhysicsObject::getNormalizedVelocity() const
	{
		return _physics->getNormalizedVelocity();
	}
	cg::Vector2d PhysicsObject::getAcceleration() const
	{
		return _physics->getAcceleration();
	}

	void PhysicsObject::setRotationFactor(double factor)
	{
		_physics->setRotationFactor(factor);
	}

	double PhysicsObject::getRotationFactor(void)
	{
		return _physics->getRotationFactor();
	}

	double PhysicsObject::getRotation() const
	{
		return _physics->getRotation();
	}

	double PhysicsObject::getRotation(bool inDegrees) const
	{
		return _physics->getRotation(inDegrees);
	}
	void PhysicsObject::setRotation(double radiansRotation)
	{
		_physics->setRotation(radiansRotation);
	}

	cg::Vector2d PhysicsObject::getUniverseDimensions(void)
	{
		return _physics->getUniverseDimensions();
	}
	void PhysicsObject::setPosition(cg::Vector2d position)
	{
		_physics->setPosition(position);
	}
	cg::Vector2d PhysicsObject::getPosition() const
	{
		return _physics->getPosition();
	}
	double PhysicsObject::getCollisionRadius()
	{
		return _physics->getCollisionRadius();
	}
	cg::Vector2d PhysicsObject::getCollisionCenter()
	{
		return _physics->getCollisionCenter();
	}
	void PhysicsObject::setCollisionRadius(double collisionRadius)
	{
		_physics->setCollisionRadius(collisionRadius);
	}
	void PhysicsObject::setCollisionCenter(cg::Vector2d collisionCenter)
	{
		_physics->setCollisionCenter(collisionCenter);
	}
	bool PhysicsObject::collidesWith(PhysicsObject *pobject)
	{
		return _physics->collidesWith(pobject);
	}
	void PhysicsObject::calculateCollision(PhysicsObject *pobject)
	{
		_physics->calculateCollision(pobject);
	}

	void PhysicsObject::rotate(double factor)
	{
		_physics->rotate(factor);
	}

	void PhysicsObject::setUniverseDimensions(int width, int height)
	{
		_physics->setUniverseDimensions(width, height);
	}

	void PhysicsObject::update(unsigned long elapsed_millis)
	{
		_physics->update(elapsed_millis);
	}

	bool PhysicsObject::penetrates(PhysicsObject *pobject)
	{
		return _physics->penetrates(pobject);
	}
	void PhysicsObject::stepBack(void)
	{
		_physics->stepBack();
	}
} // namespace asteroids
