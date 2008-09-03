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
		shutdown();
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
	
	Particle * ParticleManager::getParticle(std::string id) {
		return get(id);
	}
	
	void ParticleManager::addParticle(Particle * p) {
		_newParticles.push_back(p);
	}

	void ParticleManager::postUpdate(unsigned long elapsed_millis) {

	}

	unsigned int ParticleManager::size() {
		return (unsigned int)_particles.size();
	}
	
	
	bool ParticleManager::exists(const std::string& id) {
		return (_particleMap.count(id) != 0);
	}
	
	Particle* ParticleManager::get(const std::string& id) {
		pMapIterator i = _particleMap.find(id);
		if(i != _particleMap.end()) {
			return i->second;
		}
		return 0;
	}
	void ParticleManager::add(Particle* particle) {
		std::string id = particle->getId();
		std::pair<pMapIterator,bool> result = _particleMap.insert(std::make_pair(id, particle));
		if(result.second == false) {
			throw std::runtime_error("[ParticleManager::Particle] entity '" + id + "' already exists.");
		} else {
			_particles.push_back(particle);
		}
		cg::Group::add((Entity *)particle);
	}
	void ParticleManager::remove(const std::string& id) {
		pMapIterator i = _particleMap.find(id);
		if(i != _particleMap.end()) {
			particleIterator j = find(_particles.begin(),_particles.end(),i->second);
			_particles.erase(j);
			_particleMap.erase(id);
		}
		cg::Group::remove(id);
	}

	void ParticleManager::removeAll() {
		_particleMap.clear();
		_particles.clear();
		cg::Group::removeAll();
	}
	
	void ParticleManager::destroy(const std::string& id) {
		remove(id); //can'd delete the object yet, it's being referenced from the "Group" part
		cg::Group::destroy(id);
	}
	void ParticleManager::destroyAll() {
		removeAll(); //can't delete them yet, they're being referenced from the "Group" part
		cg::Group::destroyAll();
	}

	void ParticleManager::shutdown() {
		_newParticles.clear();
		for (std::vector<std::string>::iterator p = _deletedParticles.begin( ); p != _deletedParticles.end(); ++p) {
			destroy(*p);
		}
		_deletedParticles.clear();		
		destroyAll();
	}

	std::vector<Particle*>* ParticleManager::getParticles() {
		return &_particles; 
	}
	std::vector<Particle*>::iterator ParticleManager::beginp() { 
		return _particles.begin(); 
	}
	std::vector<Particle*>::iterator ParticleManager::endp() { 
		return _particles.end(); 
	}
	
	
	double ParticleManager::randomBetween(double min, double max) {
		return (rand() / (double)RAND_MAX * (max - min)) + min;
	}

	
	
	
}

