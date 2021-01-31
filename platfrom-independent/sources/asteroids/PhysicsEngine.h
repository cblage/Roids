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
#pragma once
#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
#pragma message("PhysicsEngine is included")

#include <string>
#include <vector>
#include "cg.h"
#include <cmath>

namespace asteroids
{
	const double PI4 = 4.0 * atan(1.0);
	class PhysicsObject;

	class PhysicsEngine
	{
	private:
		cg::Vector2d _position, _previousPosition;
		cg::Vector2d _velocity, _previousVelocity;
		double _acelFactor;
		cg::Vector2d _minVelocity, _acceleration, _previousAcceleration;
		bool _withRotation, _withMinVelocity, _accelerating;
		double _rotFactor, _rotationDeg, _rotationRad, _previousRotationRad;
		bool _rotating;
		double _universeWidth, _universeHeight;
		double _collisionRadius;
		double _mass;
		cg::Vector2d _collisionCenter, _previousCollisionCenter;
		double _previousElapsedMillis;
		bool _hasUpdated;
		double _restitutionFactor;

	public:
		PhysicsEngine();
		PhysicsEngine(double mass);
		PhysicsEngine(cg::Vector2d velocity, cg::Vector2d position);
		PhysicsEngine(cg::Vector2d velocity, cg::Vector2d position, double mass);

		virtual ~PhysicsEngine();

		double getMass(void);
		void setMass(double mass);
		void startAcceleration(double factor, bool withRotation);
		void startAcceleration(double factor, bool withRotation, cg::Vector2d minVelocity);
		void stopAcceleration();
		void setAcceleration(cg::Vector2d acceleration);
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
		void setRotation(double radiansRotation);
		void rotate(double factor);
		void update(unsigned long elapsed_millis);
		cg::Vector2d getUniverseDimensions(void);
		double getCollisionRadius();
		cg::Vector2d getCollisionCenter();
		void setCollisionRadius(double collisionRadius);
		void setCollisionCenter(cg::Vector2d collisionCenter);
		bool collidesWith(PhysicsObject *pobject);
		void calculateCollision(PhysicsObject *pobject);
		bool stepBack(void);
		bool penetrates(PhysicsObject *pobject);
		cg::Vector2d constrainVector(cg::Vector2d vector);
		double getDistance(cg::Vector2d vectorA, cg::Vector2d vectorB);
		void setRotationFactor(double factor);
		double getRotationFactor(void);
	};
} // namespace asteroids

#endif
