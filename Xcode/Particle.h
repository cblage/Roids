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
		public cg::IKeyboardEventListener,
		public cg::IDrawOverlayListener,
		public PhysicsObject
	{
	private:
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
		virtual void onKeyPressed(unsigned char key) {}
		virtual void onKeyReleased(unsigned char key) {}
		virtual void onSpecialKeyPressed(int key){}
		virtual void onSpecialKeyReleased(int key) {}
		virtual void drawOverlay() {}
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
	
#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
	class Asteroid;
	class LaserShot;
	class Particle;

	class ParticleManager : public cg::Group,
	public cg::GroupDraw,
	public cg::GroupUpdate,
	public cg::GroupKeyboardEvent,
	public cg::GroupReshapeEvent,
	public cg::GroupDrawOverlay
	{
	protected:
		std::string _numParticlesMessage;
		std::vector<std::string> _deletedParticles;
		std::vector<Particle *> _newParticles;
		
		unsigned int _currIdNum;
		
		virtual void createEntities();
		virtual void postInit();
	public:
		ParticleManager(std::string id);
		~ParticleManager();
		virtual void destroyParticle(std::string id);
		virtual void preUpdate(unsigned long elapsed_millis);
		virtual void postUpdate(unsigned long elapsed_millis);
		virtual void createAsteroids(unsigned int numAsteroids, double scaleFactor, double radius, cg::Vector2d position, double scaleDelta = 0);
		virtual void createAsteroids(unsigned int numAsteroids, double scaleFactor, double scaleDelta = 0);
		virtual void createAsteroids(unsigned int numAsteroids);
		virtual void createAsteroid(double scaleFactor, cg::Vector2d position);
		virtual void createAsteroid(double scaleFactor, cg::Vector2d position, cg::Vector2d velocity);
		virtual void createAsteroid(cg::Vector2d position);
		virtual void createAsteroid(void);
		virtual void createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation);
		virtual void createShip(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation);
		virtual void createShip(void);
		virtual void preDrawOverlay();
		virtual double randomBetween(double min, double max);
		virtual std::vector<Particle*> getParticles();
		virtual void addParticle(Particle * p);
		virtual Particle * getParticle(std::string id);
	};
#endif
}

#endif