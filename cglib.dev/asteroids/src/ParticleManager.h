#pragma once
#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
#pragma message("ParticleManager is included")
#include <sstream>
#include <string>
#include <vector>
#include "cg/cg.h"
#include "Asteroid.h"
#include "LaserShot.h"
#include "Particle.h"



namespace asteroids {
	
	class ParticleManager : public cg::Group,
		public cg::GroupDraw,
		public cg::GroupUpdate,
		public cg::GroupReshapeEvent,
		public cg::IDrawOverlayListener
	{
	private:
		std::string _numParticlesMessage;
		std::vector<std::string> _deletedParticles;
		std::vector<Particle *> _newParticles;

		unsigned int _currIdNum;
		SpaceShip * _ship;
	protected:
		void createEntities();
		void postInit();
	public:
		ParticleManager(std::string id, SpaceShip * ship);
		~ParticleManager();
		void destroyParticle(std::string id);
		void drawOverlay();
		void preUpdate(unsigned long elapsed_millis);
		void postUpdate(unsigned long elapsed_millis);
		void createAsteroids(unsigned int numAsteroids, double scaleFactor, cg::Vector2d position);
		void createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity);
		double randomBetween(double min, double max);
		SpaceShip * getSpaceShip(void);
		std::vector<Particle*> getParticles();
	};
}

#endif