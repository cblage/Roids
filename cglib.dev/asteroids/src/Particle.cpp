#include "Particle.h"

namespace asteroids {

	Particle::Particle(std::string id, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false) {};

	Particle::~Particle() {
	}

	void Particle::setDestroyed(bool destroyed) {
		_destroyed = destroyed;
	}
	
	bool Particle::isDestroyed(void){
		return _destroyed;
	}
	
	ParticleManager * Particle::getParticleManager(void) {
		return _particleManager;
	}
}
