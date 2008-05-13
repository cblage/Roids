#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#pragma message("Particle is included")
#include "SpaceShip.h"
#include "PhysicsObject.h"
#include "cg/cg.h"


namespace asteroids {
	class SpaceShip;
	class ParticleManager;

	class Particle : public cg::Entity,
		public PhysicsObject
	{
	private:
		ParticleManager * _particleManager;
		bool _destroyed;
		double _strength;
		double _penetrationTime;
		double _maxPenetrationTime;

	public:
		Particle(std::string id, ParticleManager * particleManager);
		Particle(std::string id, double strength, ParticleManager * particleManager);
		Particle(std::string id, ParticleManager * particleManager, double mass);
		Particle(std::string id, double strength, ParticleManager * particleManager, double mass);
		virtual ~Particle();
		virtual void setDestroyed(bool destroyed);
		virtual bool isDestroyed(void);
		virtual ParticleManager * getParticleManager(void);
		virtual void setStrength(double strength);
		virtual double getStrength(void);
		virtual void checkCollisions(double long elapsed_millis);
		virtual void destroy(void);

	};
	
#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H
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
		void createLaserShot(cg::Vector2d position, double radiansRotation);
		double randomBetween(double min, double max);
		SpaceShip * getSpaceShip(void);
		std::vector<Particle*> getParticles();
	};
#endif
}

#endif