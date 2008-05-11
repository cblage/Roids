#include "Particle.h"

namespace asteroids {

	Particle::Particle(std::string id, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(0),
		PhysicsObject() {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		PhysicsObject() {};
	
	Particle::Particle(std::string id, ParticleManager * particleManager, double mass) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(0),
		PhysicsObject(mass) {};

	Particle::Particle(std::string id, double strength, ParticleManager * particleManager, double mass) : cg::Entity(id),
		_particleManager(particleManager),
		_destroyed(false),
		_strength(strength),
		PhysicsObject(mass) {};

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

	void Particle::setStrength(double strength) {
		_strength = strength;
	}
	double Particle::getStrength(void) {
		return _strength;
	}
}
