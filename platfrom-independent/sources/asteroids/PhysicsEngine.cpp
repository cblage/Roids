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
#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "Maths.h"

namespace asteroids
{

	PhysicsEngine::PhysicsEngine()
	{
		_previousVelocity = cg::Vector2d(0, 0);
		_previousRotationRad = 0;
		_previousPosition = cg::Vector2d(0, 0);
		_previousCollisionCenter = cg::Vector2d(0, 0);
		_previousAcceleration = cg::Vector2d(0, 0);
		_velocity = cg::Vector2d(0, 0);
		_position = cg::Vector2d(0, 0);
		_acelFactor = 0;
		_minVelocity = cg::Vector2d(0, 0);
		_acceleration = cg::Vector2d(0, 0);
		_withRotation = false;
		_withMinVelocity = false;
		_accelerating = false;
		_rotFactor = 0;
		_rotationDeg = 0;
		_rotationRad = 0;
		_rotating = false;
		_collisionCenter = cg::Vector2d(0, 0);
		_collisionRadius = 0;
		_universeWidth = 0;
		_universeHeight = 0;
		_mass = 1;
		_hasUpdated = false;
		_restitutionFactor = cg::Properties::instance()->getDouble("COLLISION_RESTITUTION_FACTOR");
	}

	PhysicsEngine::PhysicsEngine(double mass)
	{
		_previousVelocity = cg::Vector2d(0, 0);
		_previousRotationRad = 0;
		_previousPosition = cg::Vector2d(0, 0);
		_previousCollisionCenter = cg::Vector2d(0, 0);
		_previousAcceleration = cg::Vector2d(0, 0);
		_velocity = cg::Vector2d(0, 0);
		_position = cg::Vector2d(0, 0);
		_acelFactor = 0;
		_minVelocity = cg::Vector2d(0, 0);
		_acceleration = cg::Vector2d(0, 0);
		_withRotation = false;
		_withMinVelocity = false;
		_accelerating = false;
		_rotFactor = 0;
		_rotationDeg = 0;
		_rotationRad = 0;
		_rotating = false;
		_collisionCenter = cg::Vector2d(0, 0);
		_collisionRadius = 0;
		_universeWidth = 0;
		_universeHeight = 0;
		_mass = mass;
		_hasUpdated = false;
		_restitutionFactor = cg::Properties::instance()->getDouble("COLLISION_RESTITUTION_FACTOR");
	}

	PhysicsEngine::PhysicsEngine(cg::Vector2d velocity, cg::Vector2d position)
	{
		_previousVelocity = cg::Vector2d(0, 0);
		_previousRotationRad = 0;
		_previousPosition = cg::Vector2d(0, 0);
		_previousCollisionCenter = cg::Vector2d(0, 0);
		_previousAcceleration = cg::Vector2d(0, 0);
		_velocity = velocity;
		_position = position;
		_acelFactor = 0;
		_minVelocity = cg::Vector2d(0, 0);
		_acceleration = cg::Vector2d(0, 0);
		_withRotation = false;
		_withMinVelocity = false;
		_accelerating = false;
		_rotFactor = 0;
		_rotationDeg = 0;
		_rotationRad = 0;
		_rotating = false;
		_collisionCenter = cg::Vector2d(0, 0);
		_collisionRadius = 0;
		_universeWidth = 0;
		_universeHeight = 0;
		_hasUpdated = false;
		_mass = 1;
		_restitutionFactor = cg::Properties::instance()->getDouble("COLLISION_RESTITUTION_FACTOR");
	}
	PhysicsEngine::PhysicsEngine(cg::Vector2d velocity, cg::Vector2d position, double mass)
	{
		_previousVelocity = cg::Vector2d(0, 0);
		_previousRotationRad = 0;
		_previousPosition = cg::Vector2d(0, 0);
		_previousCollisionCenter = cg::Vector2d(0, 0);
		_previousAcceleration = cg::Vector2d(0, 0);
		_velocity = velocity;
		_position = position;
		_acelFactor = 0;
		_minVelocity = cg::Vector2d(0, 0);
		_acceleration = cg::Vector2d(0, 0);
		_withRotation = false;
		_withMinVelocity = false;
		_accelerating = false;
		_rotFactor = 0;
		_rotationDeg = 0;
		_rotationRad = 0;
		_rotating = false;
		_collisionCenter = cg::Vector2d(0, 0);
		_collisionRadius = 0;
		_universeWidth = 0;
		_universeHeight = 0;
		_mass = mass;
		_hasUpdated = false;
		_restitutionFactor = cg::Properties::instance()->getDouble("COLLISION_RESTITUTION_FACTOR");
	}

	PhysicsEngine::~PhysicsEngine()
	{
	}

	double PhysicsEngine::getMass(void)
	{
		return _mass;
	}

	void PhysicsEngine::setMass(double mass)
	{
		_mass = mass;
	}

	void PhysicsEngine::setUniverseDimensions(int width, int height)
	{
		_universeWidth = width;
		_universeHeight = height;
	}

	void PhysicsEngine::setVelocity(cg::Vector2d velocity)
	{
		_velocity = velocity;
	}

	void PhysicsEngine::setPosition(cg::Vector2d position)
	{
		_position = constrainVector(position);
	}

	void PhysicsEngine::setAcceleration(cg::Vector2d acceleration)
	{
		_acceleration = acceleration;
	}

	cg::Vector2d PhysicsEngine::getUniverseDimensions(void)
	{
		return cg::Vector2d(_universeWidth, _universeHeight);
	}

	cg::Vector2d PhysicsEngine::getNormalizedVelocity() const
	{
		return normalize(_velocity);
	}

	void PhysicsEngine::startAcceleration(double factor, bool withRotation)
	{
		_accelerating = true;
		_acelFactor = factor;
		_withMinVelocity = false;
		_withRotation = withRotation;
	}

	void PhysicsEngine::startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity)
	{
		_acelFactor = factor;
		_withMinVelocity = true;
		_minVelocity = minVelocity;
		_withRotation = withRotation;
		_accelerating = true;
	}

	void PhysicsEngine::stopAcceleration()
	{
		_accelerating = false;
	}

	cg::Vector2d PhysicsEngine::constrainVector(cg::Vector2d vector)
	{
		vector[0] = realMod(vector[0], _universeWidth);
		vector[1] = realMod(vector[1], _universeHeight);
		return vector;
	}

	double PhysicsEngine::getDistance(cg::Vector2d vectorA, cg::Vector2d vectorB)
	{
		double x = std::min(realMod(abs(vectorA[0] - vectorB[0]) + _universeWidth, _universeWidth), realMod(_universeWidth - abs(vectorA[0] - vectorB[0]), _universeWidth));
		double y = std::min(realMod(abs(vectorA[1] - vectorB[1]) + _universeHeight, _universeHeight), realMod(_universeHeight - abs(vectorA[1] - vectorB[1]), _universeHeight));
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	void PhysicsEngine::update(unsigned long elapsed_millis)
	{
		_hasUpdated = true;
		_previousElapsedMillis = elapsed_millis;
		_previousVelocity = _velocity;
		_previousAcceleration = _acceleration;
		_previousPosition = _position;
		_previousRotationRad = _rotationRad;
		_previousCollisionCenter = _collisionCenter;

		double elapsed_seconds = elapsed_millis / 1000.0;

		//ROTATION UPDATE
		if (_rotating == true)
			rotate(_rotFactor * elapsed_seconds);

		if (_accelerating == true)
		{
			if (_withMinVelocity == true)
			{
				accelerate(_acelFactor * elapsed_seconds, _withRotation, _minVelocity);
			}
			else
			{
				accelerate(_acelFactor * elapsed_seconds, _withRotation);
			}
		}
		_position = constrainVector(_position + _velocity * elapsed_seconds);
		setCollisionCenter(getPosition());
	}

	bool PhysicsEngine::stepBack(void)
	{
		if (_hasUpdated == false)
			return false;

		setPosition(_previousPosition);
		//setRotation(_previousRotationRad);
		setVelocity(_previousVelocity);
		setAcceleration(_previousAcceleration);
		setCollisionCenter(_previousCollisionCenter);
		return true;
	}

	void PhysicsEngine::accelerate(double factor, bool withRotation)
	{
		if (withRotation == true)
		{
			_acceleration = cg::Vector2d(cos(getRotation()), sin(getRotation())) * factor / _mass;
		}
		else
		{
			_acceleration = getNormalizedVelocity() * factor / _mass;
		}

		cg::Vector2d newVelocity = _velocity + _acceleration;
		if (abs(newVelocity[0]) < 1)
		{
			newVelocity[0] = 0;
			_acceleration[0] = 0;
		}
		if (abs(newVelocity[1]) < 1)
		{
			newVelocity[1] = 0;
			_acceleration[1] = 0;
		}
		_velocity = newVelocity;
	}

	void PhysicsEngine::accelerate(double factor, bool withRotation, cg::Vector2d minVelocity)
	{
		if (withRotation == true)
		{
			_acceleration = cg::Vector2d(cos(getRotation()), sin(getRotation())) * factor / _mass;
		}
		else
		{
			_acceleration = getNormalizedVelocity() * factor / _mass;
		}
		cg::Vector2d newVelocity = _velocity + _acceleration;
		if (abs(newVelocity[0]) < minVelocity[0] || abs(newVelocity[0]) < 5)
		{
			newVelocity[0] = 0;
			_acceleration[0] = 0;
		}
		if (abs(newVelocity[1]) < minVelocity[1] || abs(newVelocity[1]) < 5)
		{
			newVelocity[1] = 0;
			_acceleration[1] = 0;
		}

		_velocity = newVelocity;
	}

	cg::Vector2d PhysicsEngine::getAcceleration() const
	{
		return _acceleration;
	}

	cg::Vector2d PhysicsEngine::getVelocity() const
	{
		return _velocity;
	}

	cg::Vector2d PhysicsEngine::getPosition() const
	{
		return _position;
	}

	void PhysicsEngine::startRotator(double factor)
	{
		_rotating = true;
		_rotFactor = factor;
	}

	void PhysicsEngine::setRotationFactor(double factor)
	{
		_rotFactor = factor;
	}

	double PhysicsEngine::getRotationFactor(void)
	{
		return _rotFactor;
	}

	void PhysicsEngine::stopRotator()
	{
		_rotating = false;
	}

	void PhysicsEngine::rotate(double factor)
	{
		_rotationDeg = realMod(_rotationDeg + factor, 360);
		_rotationRad = _rotationDeg * PI4 / 180;
	}

	double PhysicsEngine::getRotation() const
	{
		return _rotationRad;
	}
	double PhysicsEngine::getRotation(bool inDegrees) const
	{
		return (inDegrees == true) ? _rotationDeg : _rotationRad;
	}
	void PhysicsEngine::setRotation(double radiansRotation)
	{
		_rotationRad = realMod(radiansRotation, PI4);
		_rotationDeg = _rotationRad * 180 / PI4;
	}

	double PhysicsEngine::getCollisionRadius()
	{
		return _collisionRadius;
	}
	cg::Vector2d PhysicsEngine::getCollisionCenter()
	{
		return _collisionCenter;
	}
	void PhysicsEngine::setCollisionRadius(double collisionRadius)
	{
		_collisionRadius = collisionRadius;
	}
	void PhysicsEngine::setCollisionCenter(cg::Vector2d collisionCenter)
	{
		_collisionCenter = constrainVector(collisionCenter);
	}
	bool PhysicsEngine::collidesWith(PhysicsObject *pobject)
	{
		return (getDistance(getCollisionCenter(), pobject->getCollisionCenter()) <= (pobject->getCollisionRadius() + getCollisionRadius() - 5));
	}
	bool PhysicsEngine::penetrates(PhysicsObject *pobject)
	{
		return (getDistance(getCollisionCenter(), pobject->getCollisionCenter()) < (pobject->getCollisionRadius() + getCollisionRadius() - 5));
	}

	void PhysicsEngine::calculateCollision(PhysicsObject *pobject)
	{
		if (!collidesWith(pobject))
			return;

		unsigned long newElapsedMillis = _previousElapsedMillis / 2;
		unsigned long originalElapsedMillis = _previousElapsedMillis;
		bool steppedBack = false;

		while (newElapsedMillis > 0 && penetrates(pobject))
		{
			steppedBack = stepBack();
			update(newElapsedMillis);
			newElapsedMillis /= 2;
		}

		cg::Vector2d normalVelocity = normalize(constrainVector(getCollisionCenter() - pobject->getCollisionCenter()));
		cg::Vector2d relativeVelocity = getVelocity() - pobject->getVelocity();

		double j = (-(1 + _restitutionFactor) * dot(relativeVelocity, normalVelocity)) / (dot(normalVelocity, normalVelocity) * (1 / getMass() + 1 / pobject->getMass()));
		setVelocity(getVelocity() + (j * normalVelocity) / getMass());
		pobject->setVelocity(pobject->getVelocity() + (-j * normalVelocity) / pobject->getMass());
		if (steppedBack)
		{
			update(originalElapsedMillis - newElapsedMillis);
		}
	}
} // namespace asteroids
