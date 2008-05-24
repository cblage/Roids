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
		public cg::GroupKeyboardEvent,
		public cg::IDrawOverlayListener
	{
	private:
		std::string _numParticlesMessage;
		std::vector<std::string> _deletedParticles;
		std::vector<Particle *> _newParticles;

		unsigned int _currIdNum;
	protected:
		void createEntities();
		void postInit();
	public:
		ParticleManager(std::string id);
		~ParticleManager();
		void destroyParticle(std::string id);
		void drawOverlay();
		void preUpdate(unsigned long elapsed_millis);
		void postUpdate(unsigned long elapsed_millis);
		void createAsteroids(unsigned int numAsteroids, double scaleFactor, double radius, cg::Vector2d position);
		void createLaserShot(cg::Vector2d position, double radiansRotation, cg::Vector2d velocity, double degreesRotation);
		double randomBetween(double min, double max);
		std::vector<Particle*> getParticles();
	};
#endif
}

#endif