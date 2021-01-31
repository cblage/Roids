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
#ifndef ASTEROID_H
#define ASTEROID_H
#pragma message("Asteroid is included")
#include <string>
#include <vector>
#include "cg.h"
#include <cmath>
#include "GameEntity.h"

namespace asteroids
{
	class GameManager;
	class Particle;
	class SpaceShip;

	class Asteroid : public cg::IDrawListener,
					 public cg::IUpdateListener,
					 public GameEntity
	{
	private:
		std::vector<cg::Vector3d> _asteroid_vector, _asteroid_vector2;
		cg::Vector2d _size;
		double _scaleFactor, _radius, _invulSeconds, _baseAsteroidSize, _baseAsteroidMass;
		double _radarSize, _radarAdvanced;
		double _red, _green, _blue;
		bool _skipColoring;

	public:
		Asteroid(std::string id, GameManager *gameManager);
		Asteroid(std::string id, double scaleFactor, GameManager *gameManager);
		Asteroid(std::string id, double scaleFactor, GameManager *gameManager, double red, double green, double blue);
		~Asteroid();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		bool collidesWith(PhysicsObject *pobject);
		void checkCollisions(double long elapsed_millis);
		void destroy(void);
		void drawOverlay(void);
	};
} // namespace asteroids

#endif
