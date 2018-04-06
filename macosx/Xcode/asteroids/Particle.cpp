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
#include "Particle.h"
#include "ParticleManager.h"

namespace asteroids {

	Particle::Particle(std::string id, ParticleManager * particleManager, char particleType) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(1),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		_particleType(particleType),
		PhysicsObject() {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager, char particleType) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		_particleType(particleType),
		PhysicsObject() {};
	
	Particle::Particle(std::string id, ParticleManager * particleManager, double mass, char particleType) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(1),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		_particleType(particleType),
		PhysicsObject(mass) {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager, double mass, char particleType) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		_penetrationTime(0),
		_maxPenetrationTime(cg::Properties::instance()->getDouble("PARTICLE_MAX_PENETRATE")),
		_particleType(particleType),
		PhysicsObject(mass) {};

	Particle::~Particle() {
	}

	void Particle::setDestroyed(bool destroyed) {
		_destroyed = destroyed;
	}
	
	bool Particle::isDestroyed(void){
		return _destroyed;
	}
	
	ParticleManager * Particle::getParticleManager(void) {
		return _particleManager;
	}

	void Particle::setStrength(double strength) {
		_strength = strength;
	}
	double Particle::getStrength(void) {
		return _strength;
	}

	void Particle::setHealth(double health) {
		if(isDestroyed() == true)
			return;

		_health = health;
		if(_health < 1) {
			destroy();
		}
	}
	
	void Particle::initHealth(double health) {
		_health = health;
		_initHealth = health;
	}

	double Particle::getMaxHealth(void) {
		return _initHealth;
	}

	double Particle::getHealth(void) {
		if(isDestroyed() == true)
			return 0;

		return _health;
	}
	
	double Particle::getHealth(bool percentage) {
		if (percentage == false) 
			return getHealth();
		
		return 100 * getHealth()/getMaxHealth();
	}

	void Particle::dealDamage(double damage) {
		if(isDestroyed() == true)
			return;
		
		setHealth(getHealth() - damage);
	}


	void Particle::checkCollisions(double long elapsed_millis) {
		if(isDestroyed() == true)
			return;
		
		if(_penetrationTime > _maxPenetrationTime) {
			destroy();
			return;
		}

		std::vector<Particle*>* particles = getParticleManager()->getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles->size(); i++) {
			if((*particles)[i]->getId() == _id)
				continue;
			processParticleCollision((*particles)[i]);
			if(isDestroyed() == true)
				return;
			if(penetrates((*particles)[i])) {
				_penetrationTime += elapsed_millis / 1000.0;
			} 
		}
	}

	void Particle::destroy(void) {
		setDestroyed(true);
		getParticleManager()->destroyParticle(getId());
	}
	
	void Particle::processParticleCollision(Particle * p) {
		if(!collidesWith(p) || p->isDestroyed())
			return;

		double dealtDamage, recievedDamage;
		recievedDamage = p->getCollisionDamage(this);
		dealtDamage = getCollisionDamage(p);
		calculateCollision(p);
		dealDamage(recievedDamage);
		p->dealDamage(dealtDamage);
	}

	double Particle::getCollisionDamage(Particle * target) {
		//default damage dealt by a particle to another particle during a collision
		return (getStrength()/target->getStrength()) * (getMass()/target->getMass()) * length(target->getVelocity() - getVelocity());
	}

	char Particle::getParticleType() {
		return _particleType;
	}
	
	void Particle::setParticleType(char particleType) {
		_particleType = particleType;
	}
		
	void Particle::onReshape(int width, int height) {
		if(width > 100 && height > 100) {
			setUniverseDimensions(width,height);
		}
	}	
	
}


