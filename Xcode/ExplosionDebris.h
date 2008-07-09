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
#ifndef EXPLOSIONDEBRIS_H
#define EXPLOSIONDEBRIS_H
#pragma message("ExplosionDebris is included")

#include <string>
#include <vector>
#include "cg/cg.h"
#include <cmath>
#include "Particle.h"


namespace asteroids {
	class ParticleManager;
	class SpaceShip;
	class PhysicsObject;
	class Particle;

	class ExplosionDebris : public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public Particle
	{
	private:
		double _maxSecondsToLive, _secondsToLive, _radius, _alpha;
		cg::Vector3d _color;
		
	public:
		ExplosionDebris(std::string id, ParticleManager * particleManager, cg::Vector3d color = cg::Vector3d(0.7, 0.7, 0.7));
		~ExplosionDebris();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
		bool collidesWith(PhysicsObject *pobject);
		double randomBetween(double min, double max);
	};
}

#endif
