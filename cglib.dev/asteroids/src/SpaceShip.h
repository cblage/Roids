#pragma once
#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H
#pragma message("SpaceShip is included")

#include <string>
#include "cg/cg.h"
#include <cmath>
#include "PhysicsObject.h"
#include "SpaceShipHyperAccelerator.h"



namespace asteroids {
	class ParticleManager;
	class SpaceShipHyperAccelerator;

	class SpaceShip : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener,
		public cg::IReshapeEventListener,
		public cg::IDrawOverlayListener,
		public PhysicsObject
	{
	private:
		cg::Vector2d _size;
		double _winWidth, _winHeight, _charlesBronsonKilledSecondsAgo;		
		SpaceShipHyperAccelerator * _hyperAccelerator;
		ParticleManager * _particleManager;
		int _charlesBronsonStyle;
	public:
		SpaceShip(std::string id);
		~SpaceShip();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void drawOverlay();
        void onReshape(int width, int height);
		void hyperAccelerate(void);
		void setParticleManager(ParticleManager *particleManager);
		void shootLaser(void);
	};
}




#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
namespace asteroids {
	class Asteroid;
	class LaserShot;
	class Particle;

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



#endif