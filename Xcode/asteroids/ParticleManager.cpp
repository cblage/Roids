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
#include "ParticleManager.h"
#include "Particle.h"

namespace asteroids {

	ParticleManager::ParticleManager(std::string id) : cg::Group(id), _currIdNum(0) {
	}
	ParticleManager::~ParticleManager() {
		_newParticles.clear();
		for (std::vector<std::string>::iterator p = _deletedParticles.begin( ); p != _deletedParticles.end(); ++p) {
			destroy(*p);
		}
		_deletedParticles.clear();
	}
	void ParticleManager::createEntities() {
	}
	void ParticleManager::postInit() {
		std::ostringstream os;
		os << size() << " particles on screen.";
		_numParticlesMessage = os.str();
	}
	
	void ParticleManager::destroyParticle(std::string id) {
		_deletedParticles.push_back(id);
	}

	void ParticleManager::preUpdate(unsigned long elapsed_millis) {
		for (std::vector<std::string>::iterator p = _deletedParticles.begin( ); p != _deletedParticles.end(); ++p) {
		  destroy(*p);
		}
		_deletedParticles.clear();
		for (std::vector<Particle*>::iterator q = _newParticles.begin( ); q != _newParticles.end(); ++q) {
		  add(*q);
		}
		_newParticles.clear();


		std::ostringstream os;
		os << size() << " particles on screen.";
		_numParticlesMessage = os.str();
	}

	std::vector<Particle*> ParticleManager::getParticles() {
		//ODEIO-TE ENTITIES!!!!!!!!!!!!!!
		std::vector<Particle*> particles;
		for (std::vector<Entity*>::iterator p = cg::Group::begin(); p != cg::Group::end( ); p++) {
			particles.push_back(dynamic_cast<Particle*>(*p));
		}
		return particles;
	}
	
	Particle * ParticleManager::getParticle(std::string id) {
		return dynamic_cast<Particle *>(get(id));
	}
	
	void ParticleManager::addParticle(Particle * p) {
		_newParticles.push_back(p);
	}

	void ParticleManager::postUpdate(unsigned long elapsed_millis) {

	}


	double ParticleManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

}