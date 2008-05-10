#ifndef PARTICLE_H
#define PARTICLE_H


#include "cg/cg.h"


namespace asteroids {
	class ParticleManager;
	class Particle : public cg::Entity
	{
	private:
		ParticleManager * _particleManager;
		bool _destroyed;

	public:
		Particle(std::string id, ParticleManager * particleManager);
		virtual ~Particle();
		virtual void setDestroyed(bool destroyed);
		virtual bool isDestroyed(void);
		virtual ParticleManager * getParticleManager(void);
	};
}

#endif