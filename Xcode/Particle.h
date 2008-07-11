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
#ifndef PARTICLE_H
#define PARTICLE_H
#pragma message("Particle is included")
#include "PhysicsObject.h"
#include "cg/cg.h"


namespace asteroids {
	class ParticleManager;

	class Particle : public cg::Entity,
		public PhysicsObject
	{
	protected:
		ParticleManager * _particleManager;
		bool _destroyed;
		double _strength;
		double _penetrationTime;
		double _maxPenetrationTime;
		double _health;
		double _initHealth;
		char _particleType;

	public:
		Particle(std::string id, ParticleManager * particleManager, char particleType='p');
		Particle(std::string id, double strength, ParticleManager * particleManager, char particleType='p');
		Particle(std::string id, ParticleManager * particleManager, double mass, char particleType='p');
		Particle(std::string id, double strength, ParticleManager * particleManager, double mass, char particleType='p');
		virtual ~Particle();
		virtual void setDestroyed(bool destroyed);
		virtual bool isDestroyed(void);
		virtual ParticleManager * getParticleManager(void);
		virtual void setStrength(double strength);
		virtual double getStrength(void);
		virtual void checkCollisions(double long elapsed_millis);
		virtual void destroy(void);
		virtual double getHealth(void);
		virtual void setHealth(double health);
		virtual void processParticleCollision(Particle * p);
		virtual double getCollisionDamage(Particle * target);
		virtual void dealDamage(double damage);
		virtual double getMaxHealth(void);
		virtual double getHealth(bool per);
		virtual void initHealth(double health);
		virtual char getParticleType();
		virtual void setParticleType(char particleType);

	};

}

#endif