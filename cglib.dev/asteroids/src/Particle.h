#ifndef PARTICLE_H
#define PARTICLE_H
#include "PhysicsObject.h"

#include "cg/cg.h"


namespace asteroids {
	class ParticleManager;
	class Particle : public cg::Entity,
		public PhysicsObject
	{
	private:
		ParticleManager * _particleManager;
		bool _destroyed;
		double _strength;

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

	};
}

#endif