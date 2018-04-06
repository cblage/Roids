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
#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
#pragma message("ParticleManager is included")
#include <sstream>
#include <string>
#include <vector>
#include "cg.h"


namespace asteroids {
	class Particle;
	
	class ParticleManager : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate
	{
	private:
		void shutdown();		
	protected:
		std::string _numParticlesMessage;
		std::vector<std::string> _deletedParticles;
		std::vector<Particle *> _newParticles; 
		std::vector<Particle *> _particles; 
		std::map<std::string,Particle*> _particleMap;
		typedef std::map<std::string,Particle*>::iterator pMapIterator;
		typedef std::vector<Particle *>::iterator particleIterator;
		

		unsigned int _currIdNum;
		
		void add(Particle* particle);
		virtual void createEntities();
		virtual void postInit();
		virtual unsigned int size();
		virtual bool exists(const std::string& id);
		virtual Particle *get(const std::string& id);
		virtual void remove(const std::string& id);
		virtual void removeAll();
		virtual void destroy(const std::string& id);
		virtual void destroyAll();
			
	public:
		ParticleManager(std::string id);
		~ParticleManager();
		virtual void destroyParticle(std::string id);
		virtual void preUpdate(unsigned long elapsed_millis);
		virtual void postUpdate(unsigned long elapsed_millis);
		virtual void addParticle(Particle * p);
		virtual Particle * getParticle(std::string id);
		virtual std::vector<Particle*> * getParticles();
		virtual std::vector<Particle*>::iterator beginp();
		virtual std::vector<Particle*>::iterator endp();
	};
}

#endif


