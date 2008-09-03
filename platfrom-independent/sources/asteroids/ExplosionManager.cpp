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
#include "ExplosionManager.h"
#include "ExplosionDebris.h"

namespace asteroids {
	ExplosionManager::ExplosionManager(std::string id, MyApp *application) : ParticleManager(id), _application(application) {
		_massDivider = cg::Properties::instance()->getDouble("DEBRIS_MASS_DIVIDER");
	}
	ExplosionManager::~ExplosionManager() {
	}
	
	void ExplosionManager::createEntities() {

	}

	void ExplosionManager::generateExplosion(Particle * p) { //generates an explosion for the given particle
		if(p->getParticleType() == 'l') {
			return;
		}
		double x, y, angle;
		cg::Vector2d newPosition, velocity;
		double rand, rand2;
		rand = randomBetween(0, 3.14);
		unsigned int numDebris = ceil(p->getMass()/_massDivider);
		for(unsigned int i = 0; i < numDebris; i++) {
			rand2 = randomBetween(0.1,7.0)/5.0;
 			angle = 2*(3.14)*i/numDebris+ rand + rand2;
			x = cos(angle)*randomBetween(0.5,0.9)*p->getCollisionRadius()*0.8;
			y = sin(angle)*randomBetween(0.5,0.9)*p->getCollisionRadius()*0.8;			
			newPosition = p->getPosition() + cg::Vector2d(x,y);
			velocity = normalize(cg::Vector2d(x,y))*randomBetween(50,200)+p->getVelocity(); 
			createExplosionDebris(newPosition, velocity);
		}
	}
	
	void ExplosionManager::createExplosionDebris(cg::Vector2d position, cg::Vector2d velocity, cg::Vector3d color) {
		std::ostringstream os;
		os << "ExplosionDebris" << _currIdNum++;
		ExplosionDebris * createdExplosionDebris = new ExplosionDebris(os.str(), this);
		createdExplosionDebris->init();
		createdExplosionDebris->setVelocity(velocity);
		createdExplosionDebris->setPosition(position);
		addParticle(createdExplosionDebris);
	}
	
	void ExplosionManager::clearExplosions() {
		///make sure we have a clean slate - no new particles are going to be added
		//and we dont want duplicates in the deleted ones
		_newParticles.clear();
		_deletedParticles.clear();
		
		std::vector<Particle *>* particles = getParticles();
		for(std::vector<Particle*>::size_type i = 0; i < particles->size(); i++) {
			//cant use this because asteroids would generate new ones
			//particles[i]->destroy();
			destroyParticle((*particles)[i]->getId());
		}
	}

	void ExplosionManager::preDrawOverlay() {
		
	}

}

